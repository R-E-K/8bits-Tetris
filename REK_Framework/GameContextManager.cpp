#pragma once
#include "GameContextManager.h"

namespace REKFramework
{
	GameContextManager::GameContextManager()
	{
		currentGameContext = GameContext::MENU;
		DrawPictureMngr = std::make_unique<DrawPictureManager>();

		gameMenu = nullptr;
	}


	GameContextManager::~GameContextManager()
	{
		
	}

	void GameContextManager::SetGameMenu(GameMenu* gMenu)
	{
		gameMenu = gMenu;
	}

	void GameContextManager::ExecuteAButtonAction()
	{
		switch (currentGameContext)
		{
		case GameContext::INGAME:
			DrawPictureMngr->DrawAButton();
			break;
		case GameContext::MENU:
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
		case GameContext::INGAME:
			DrawPictureMngr->DrawBButton();
			break;
		case GameContext::MENU:
			if (gameMenu != nullptr)
			{
				if (gameMenu->MustDestroyGameMenuOnBack())
				{
					CloseGameMenu();
				}
				gameMenu->MenuBack();
			}
			break;
		}
	}

	void GameContextManager::ExecuteXButtonAction()
	{
		switch (currentGameContext)
		{
		case GameContext::INGAME:
			DrawPictureMngr->DrawXButton();
			break;
		}
	}

	void GameContextManager::ExecuteYButtonAction()
	{
		switch (currentGameContext)
		{
		case GameContext::INGAME:
			DrawPictureMngr->DrawYButton();
			break;
		}
	}

	void GameContextManager::ExecuteLBButtonAction()
	{
		switch (currentGameContext)
		{
		case GameContext::INGAME:
			DrawPictureMngr->DrawLBButton();
			break;
		}
	}

	void GameContextManager::ExecuteRBButtonAction()
	{
		switch (currentGameContext)
		{
		case GameContext::INGAME:
			DrawPictureMngr->DrawRBButton();
			break;
		}
	}

	void GameContextManager::ExecuteDPadDownButtonAction()
	{
		switch (currentGameContext)
		{
		case GameContext::INGAME:
			DrawPictureMngr->DrawDPadDownButton();
			break;
		case GameContext::MENU:
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
		case GameContext::INGAME:
			DrawPictureMngr->DrawDPadUpButton();
			break;
		case GameContext::MENU:
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
		case GameContext::INGAME:
			DrawPictureMngr->DrawDPadLeftButton();
			break;
		}
	}

	void GameContextManager::ExecuteDPadRightButtonAction()
	{
		switch (currentGameContext)
		{
		case GameContext::INGAME:
			DrawPictureMngr->DrawDPadRightButton();
			break;
		}
	}

	void GameContextManager::ExecuteL3ButtonAction()
	{
		switch (currentGameContext)
		{
		case GameContext::INGAME:
			DrawPictureMngr->DrawLeftStickButton();
			break;
		}
	}

	void GameContextManager::ExecuteR3ButtonAction()
	{
		switch (currentGameContext)
		{
		case GameContext::INGAME:
			DrawPictureMngr->DrawRightStickButton();
			break;
		}
	}

	void GameContextManager::ExecuteStartButtonAction()
	{
		switch (currentGameContext)
		{
		case GameContext::INGAME:
			currentGameContext = GameContext::MENU;
			break;
		case GameContext::MENU:
			CloseGameMenu();
			break;
		}
	}

	void GameContextManager::ExecuteBackButtonAction()
	{
		switch (currentGameContext)
		{
		case GameContext::INGAME:
			DrawPictureMngr->DrawBackButton();
			break;
		case GameContext::MENU:
			if (gameMenu != nullptr)
			{
				if (gameMenu->MustDestroyGameMenuOnBack())
				{
					CloseGameMenu();
				}
				gameMenu->MenuBack();
			}
			break;
		}
	}

	void GameContextManager::ExecuteLTTriggerAction()
	{
		switch (currentGameContext)
		{
		case GameContext::INGAME:
			DrawPictureMngr->DrawLTButton();
			break;
		}
	}

	void GameContextManager::ExecuteRTTriggerAction()
	{
		switch (currentGameContext)
		{
		case GameContext::INGAME:
			DrawPictureMngr->DrawRTButton();
			break;
		}
	}

	void GameContextManager::CloseGameMenu()
	{
		currentGameContext = GameContext::INGAME;
	}
}
