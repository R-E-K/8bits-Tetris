#pragma once
#include "GamepadConfiguration.h"


namespace REKFramework
{
	GamepadConfiguration::GamepadConfiguration()
	{
		gamepad = nullptr;
	}


	GamepadConfiguration::~GamepadConfiguration()
	{
		if (gamepad != nullptr) SDL_GameControllerClose(gamepad);
	}


	void GamepadConfiguration::PlugGamepad()
	{
		if (SDL_IsGameController(0))
		{
			gamepad = SDL_GameControllerOpen(0);
			if (gamepad != nullptr)
			{
				DisplayDebugInformations();
			}
		}
	}

	void GamepadConfiguration::UnplugGamepad()
	{
		if (gamepad != nullptr)
		{
			std::cout << "Game controller " << SDL_GameControllerName(gamepad) << "Removed" << std::endl << std::endl;
			SDL_GameControllerClose(gamepad);
			gamepad = nullptr;
		}
	}

	void GamepadConfiguration::DisplayDebugInformations() const
	{
		std::cout << "Gamepad controller informations : " << std::endl;
		std::cout << "Name : " << SDL_GameControllerName(gamepad) << std::endl << std::endl;
	}
}