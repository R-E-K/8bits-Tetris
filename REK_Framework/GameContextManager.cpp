#pragma once
#include "GameContextManager.h"

namespace REKFramework
{
	GameContextManager::GameContextManager()
	{
		currentGameContext = GameContextEnum::MENU;
		DrawPictureMngr = std::make_unique<DrawPictureManager>();

		gameMenu = nullptr;
	}


	GameContextManager::~GameContextManager()
	{
		
	}

	void GameContextManager::SetGameMenu(std::shared_ptr<GameMenu> gMenu)
	{
		gameMenu = gMenu;
	}

	void GameContextManager::SetBoardGame(std::shared_ptr<Board> gBoard)
	{
		boardGame = gBoard;
	}

	void GameContextManager::ExecuteAButtonAction()
	{
		switch (currentGameContext)
		{
		case GameContextEnum::INGAME:
			if (boardGame != nullptr)
			{
				auto tetromino = boardGame->GetCurrentTetromino();
				if (tetromino != nullptr)
				{
					tetromino->RotateRight();
				}
			}
			break;
		case GameContextEnum::MENU:
			if (gameMenu != nullptr)
			{
				gameMenu->SelectItemMenu();
				if (gameMenu->MustDestroyGameMenuOnSelect())
				{
					CloseGameMenu();
				}
			}
			break;
		}
	}

	void GameContextManager::ExecuteBButtonAction()
	{
		switch (currentGameContext)
		{
		case GameContextEnum::INGAME:
			DrawPictureMngr->DrawBButton();
			break;
		case GameContextEnum::MENU:
			if (gameMenu != nullptr)
			{
				if (gameMenu->MustDestroyGameMenuOnBack())
				{
					CloseGameMenu();
				}
				else
				{
					gameMenu->MenuBack();
				}
			}
			break;
		}
	}

	void GameContextManager::ExecuteXButtonAction()
	{
		switch (currentGameContext)
		{
		case GameContextEnum::INGAME:
			if (boardGame != nullptr)
			{
				auto tetromino = boardGame->GetCurrentTetromino();
				if (tetromino != nullptr)
				{
					tetromino->RotateLeft();
				}
			}
			break;
		}
	}

	void GameContextManager::ExecuteYButtonAction()
	{
		switch (currentGameContext)
		{
		case GameContextEnum::INGAME:
			DrawPictureMngr->DrawYButton();
			break;
		}
	}

	void GameContextManager::ExecuteLBButtonAction()
	{
		switch (currentGameContext)
		{
		case GameContextEnum::INGAME:
			if (boardGame != nullptr)
			{
				auto tetromino = boardGame->GetCurrentTetromino();
				if (tetromino != nullptr)
				{
					tetromino->RotateLeft();
				}
			}
			break;
		}
	}

	void GameContextManager::ExecuteRBButtonAction()
	{
		switch (currentGameContext)
		{
		case GameContextEnum::INGAME:
			if (boardGame != nullptr)
			{
				auto tetromino = boardGame->GetCurrentTetromino();
				if (tetromino != nullptr)
				{
					tetromino->RotateRight();
				}
			}
			break;
		}
	}

	void GameContextManager::ExecuteDPadDownButtonAction()
	{
		switch (currentGameContext)
		{
		case GameContextEnum::INGAME:
			DrawPictureMngr->DrawDPadDownButton();
			break;
		case GameContextEnum::MENU:
			if (gameMenu != nullptr)
			{
				gameMenu->NavigateDown();
			}
			break;
		}
	}

	void GameContextManager::ExecuteDPadUpButtonAction()
	{
		switch (currentGameContext)
		{
		case GameContextEnum::INGAME:
			DrawPictureMngr->DrawDPadUpButton();
			break;
		case GameContextEnum::MENU:
			if (gameMenu != nullptr)
			{
				gameMenu->NavigateUp();
			}
			break;
		}
	}

	void GameContextManager::ExecuteDPadLeftButtonAction()
	{
		switch (currentGameContext)
		{
		case GameContextEnum::INGAME:
			if (boardGame != nullptr)
			{
				boardGame->MoveTetrominoToTheLeft();
			}
			break;
		}
	}

	void GameContextManager::ExecuteDPadRightButtonAction()
	{
		switch (currentGameContext)
		{
		case GameContextEnum::INGAME:
			if (boardGame != nullptr)
			{
				boardGame->MoveTetrominoToTheRight();
			}
			break;
		}
	}

	void GameContextManager::ExecuteL3ButtonAction()
	{
		switch (currentGameContext)
		{
		case GameContextEnum::INGAME:
			DrawPictureMngr->DrawLeftStickButton();
			break;
		}
	}

	void GameContextManager::ExecuteR3ButtonAction()
	{
		switch (currentGameContext)
		{
		case GameContextEnum::INGAME:
			DrawPictureMngr->DrawRightStickButton();
			break;
		}
	}

	void GameContextManager::ExecuteStartButtonAction()
	{
		switch (currentGameContext)
		{
		case GameContextEnum::INGAME:
			currentGameContext = GameContextEnum::MENU;
			break;
		case GameContextEnum::MENU:
			CloseGameMenu();
			break;
		}
	}

	void GameContextManager::ExecuteBackButtonAction()
	{
		switch (currentGameContext)
		{
		case GameContextEnum::INGAME:
			DrawPictureMngr->DrawBackButton();
			break;
		case GameContextEnum::MENU:
			if (gameMenu != nullptr)
			{
				if (gameMenu->MustDestroyGameMenuOnBack())
				{
					CloseGameMenu();
				}
				else
				{
					gameMenu->MenuBack();
				}
			}
			break;
		}
	}

	void GameContextManager::ExecuteLTTriggerAction()
	{
		switch (currentGameContext)
		{
		case GameContextEnum::INGAME:
			DrawPictureMngr->DrawLTButton();
			break;
		}
	}

	void GameContextManager::ExecuteRTTriggerAction()
	{
		switch (currentGameContext)
		{
		case GameContextEnum::INGAME:
			DrawPictureMngr->DrawRTButton();
			break;
		}
	}

	void GameContextManager::CloseGameMenu()
	{
		currentGameContext = GameContextEnum::INGAME;
		gameMenu.reset();
	}
}
