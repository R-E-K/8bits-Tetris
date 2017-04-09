#pragma once
#include "GameContextManager.h"



GameContextManager::GameContextManager()
{
	currentGameContext = MENU;
	DrawPictureMngr = new DrawPictureManager();

	gameMenu = nullptr;
}


GameContextManager::~GameContextManager()
{
	delete DrawPictureMngr;
}

void GameContextManager::SetGameMenu(GameMenu* gMenu)
{
	gameMenu = gMenu;
}

void GameContextManager::ExecuteAButtonAction()
{
	switch(currentGameContext)
	{
	case INGAME:
		DrawPictureMngr->DrawAButton();
		break;
	case MENU:
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
	case INGAME:
		DrawPictureMngr->DrawBButton();
		break;
	case MENU:
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
	case INGAME:
		DrawPictureMngr->DrawXButton();
		break;
	}
}

void GameContextManager::ExecuteYButtonAction()
{
	switch (currentGameContext)
	{
	case INGAME:
		DrawPictureMngr->DrawYButton();
		break;
	}
}

void GameContextManager::ExecuteLBButtonAction()
{
	switch (currentGameContext)
	{
	case INGAME:
		DrawPictureMngr->DrawLBButton();
		break;
	}
}

void GameContextManager::ExecuteRBButtonAction()
{
	switch (currentGameContext)
	{
	case INGAME:
		DrawPictureMngr->DrawRBButton();
		break;
	}
}

void GameContextManager::ExecuteDPadDownButtonAction()
{
	switch (currentGameContext)
	{
	case INGAME:
		DrawPictureMngr->DrawDPadDownButton();
		break;
	case MENU:
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
	case INGAME:
		DrawPictureMngr->DrawDPadUpButton();
		break;
	case MENU:
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
	case INGAME:
		DrawPictureMngr->DrawDPadLeftButton();
		break;
	}
}

void GameContextManager::ExecuteDPadRightButtonAction()
{
	switch (currentGameContext)
	{
	case INGAME:
		DrawPictureMngr->DrawDPadRightButton();
		break;
	}
}

void GameContextManager::ExecuteL3ButtonAction()
{
	switch (currentGameContext)
	{
	case INGAME:
		DrawPictureMngr->DrawLeftStickButton();
		break;
	}
}

void GameContextManager::ExecuteR3ButtonAction()
{
	switch (currentGameContext)
	{
	case INGAME:
		DrawPictureMngr->DrawRightStickButton();
		break;
	}
}

void GameContextManager::ExecuteStartButtonAction()
{
	switch (currentGameContext)
	{
	case INGAME:
		currentGameContext = MENU;
		break;
	case MENU:
		CloseGameMenu();
		break;
	}
}

void GameContextManager::ExecuteBackButtonAction()
{
	switch (currentGameContext)
	{
	case INGAME:
		DrawPictureMngr->DrawBackButton();
		break;
	case MENU:
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
	case INGAME:
		DrawPictureMngr->DrawLTButton();
		break;
	}
}

void GameContextManager::ExecuteRTTriggerAction()
{
	switch (currentGameContext)
	{
	case INGAME:
		DrawPictureMngr->DrawRTButton();
		break;
	}
}

void GameContextManager::CloseGameMenu()
{
	currentGameContext = INGAME;
}
