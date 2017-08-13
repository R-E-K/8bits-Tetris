#pragma once
#include "GameContextManager.h"

namespace REKTetrisGame
{
	// Static Initialization
	GameContextEnum GameContextManager::CurrentGameContext = GameContextEnum::STARTED;


	GameContextManager::GameContextManager()
	{
		gameMenu = nullptr;
	}


	GameContextManager::~GameContextManager()
	{
		
	}

	bool GameContextManager::IsGamePaused()
	{
		return CurrentGameContext == GameContextEnum::MENU || CurrentGameContext == GameContextEnum::GAMEOVER;
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
		case GameContextEnum::STARTED:
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
			break;
		case GameContextEnum::STARTED:
		case GameContextEnum::MENU:
			if (gameMenu != nullptr)
			{
				if (gameMenu->MustDestroyGameMenuOnBack(boardGame))
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
			if (boardGame != nullptr)
			{
				boardGame->MoveTetrominoDown();
			}
			break;
		case GameContextEnum::STARTED:
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
			break;
		case GameContextEnum::STARTED:
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
			break;
		}
	}

	void GameContextManager::ExecuteR3ButtonAction()
	{
		switch (CurrentGameContext)
		{
		case GameContextEnum::INGAME:
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
			if (boardGame == nullptr || !boardGame->IsGameOver())
			{
				CloseGameMenu();
			}
			break;
		case GameContextEnum::GAMEOVER:
			CurrentGameContext = GameContextEnum::MENU;
			break;
		}
	}

	void GameContextManager::ExecuteBackButtonAction()
	{
		switch (CurrentGameContext)
		{
		case GameContextEnum::INGAME:
			break;
		case GameContextEnum::STARTED:
		case GameContextEnum::MENU:
			if (gameMenu != nullptr)
			{
				if (gameMenu->MustDestroyGameMenuOnBack(boardGame))
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
			break;
		}
	}

	void GameContextManager::ExecuteRTTriggerAction()
	{
		switch (CurrentGameContext)
		{
		case GameContextEnum::INGAME:
			break;
		}
	}

	void GameContextManager::ExecuteDPadDownButtonReleaseAction()
	{
		switch (CurrentGameContext)
		{
		// Need to check for menu context too if, for example :
		// You hold down in game. At the same time, you press start to open the menu and then, you release down.
		// The Timer of the falling tetromino absolutely need to be reset, even in Menu context. If it's not, it will down very fast
		// when you exit menu and you have to press down again to reset it.
		case GameContextEnum::INGAME:
		case GameContextEnum::MENU:
			if (boardGame != nullptr)
			{
				boardGame->MoveTetrominoDownRelease();
			}
			break;
		}
	}

	void GameContextManager::CloseGameMenu()
	{
		CurrentGameContext = GameContextEnum::INGAME;
		gameMenu.reset();
	}
}
