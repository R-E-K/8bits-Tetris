#pragma once
#include "GameContextManager.h"

namespace REKFramework
{
	// Static Initialization
	GameContextEnum GameContextManager::CurrentGameContext = GameContextEnum::MENU;


	GameContextManager::GameContextManager()
	{
		DrawPictureMngr = std::make_unique<DrawPictureManager>();

		gameMenu = nullptr;
	}


	GameContextManager::~GameContextManager()
	{
		
	}

	bool GameContextManager::IsGamePaused()
	{
		return CurrentGameContext == GameContextEnum::MENU;
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
		switch (CurrentGameContext)
		{
		case GameContextEnum::INGAME:
			if (boardGame != nullptr)
			{
				boardGame->RotateTetrominoToRightIfPossible();
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
		switch (CurrentGameContext)
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
		switch (CurrentGameContext)
		{
		case GameContextEnum::INGAME:
			if (boardGame != nullptr)
			{
				boardGame->RotateTetrominoToLeftIfPossible();
			}
			break;
		}
	}

	void GameContextManager::ExecuteYButtonAction()
	{
		switch (CurrentGameContext)
		{
		case GameContextEnum::INGAME:
			DrawPictureMngr->DrawYButton();
			break;
		}
	}

	void GameContextManager::ExecuteLBButtonAction()
	{
		switch (CurrentGameContext)
		{
		case GameContextEnum::INGAME:
			if (boardGame != nullptr)
			{
				boardGame->RotateTetrominoToLeftIfPossible();
			}
			break;
		}
	}

	void GameContextManager::ExecuteRBButtonAction()
	{
		switch (CurrentGameContext)
		{
		case GameContextEnum::INGAME:
			if (boardGame != nullptr)
			{
				boardGame->RotateTetrominoToRightIfPossible();
			}
			break;
		}
	}

	void GameContextManager::ExecuteDPadDownButtonAction()
	{
		switch (CurrentGameContext)
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
		switch (CurrentGameContext)
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
		switch (CurrentGameContext)
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
		switch (CurrentGameContext)
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
		switch (CurrentGameContext)
		{
		case GameContextEnum::INGAME:
			DrawPictureMngr->DrawLeftStickButton();
			break;
		}
	}

	void GameContextManager::ExecuteR3ButtonAction()
	{
		switch (CurrentGameContext)
		{
		case GameContextEnum::INGAME:
			DrawPictureMngr->DrawRightStickButton();
			break;
		}
	}

	void GameContextManager::ExecuteStartButtonAction()
	{
		switch (CurrentGameContext)
		{
		case GameContextEnum::INGAME:
			CurrentGameContext = GameContextEnum::MENU;
			break;
		case GameContextEnum::MENU:
			CloseGameMenu();
			break;
		}
	}

	void GameContextManager::ExecuteBackButtonAction()
	{
		switch (CurrentGameContext)
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
		switch (CurrentGameContext)
		{
		case GameContextEnum::INGAME:
			DrawPictureMngr->DrawLTButton();
			break;
		}
	}

	void GameContextManager::ExecuteRTTriggerAction()
	{
		switch (CurrentGameContext)
		{
		case GameContextEnum::INGAME:
			DrawPictureMngr->DrawRTButton();
			break;
		}
	}

	void GameContextManager::CloseGameMenu()
	{
		CurrentGameContext = GameContextEnum::INGAME;
		gameMenu.reset();
	}
}
