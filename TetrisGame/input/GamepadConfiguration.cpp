#pragma once
#include "GamepadConfiguration.h"


namespace REKTetrisGame
{
	GamepadConfiguration::GamepadConfiguration()
	{
		_gamepad = nullptr;
	}


	GamepadConfiguration::~GamepadConfiguration()
	{
		
	}


	void GamepadConfiguration::PlugGamepad()
	{
		// The game is one player only, so we only check for first plugged gamepad
		if (SDL_IsGameController(0))
		{
			_gamepad = std::unique_ptr<SDL_GameController, SdlDeleter>(SDL_GameControllerOpen(0), SdlDeleter());
			if (_gamepad != nullptr)
			{
				DisplayDebugInformations();
			}
		}
	}

	void GamepadConfiguration::UnplugGamepad()
	{
		if (_gamepad != nullptr)
		{
			std::cout << "Game controller " << SDL_GameControllerName(_gamepad.get()) << "Removed" << std::endl << std::endl;
			_gamepad.reset();
		}
	}

	bool GamepadConfiguration::IsGamepadPlugged() const
	{
		return _gamepad != nullptr;
	}

	void GamepadConfiguration::DisplayDebugInformations() const
	{
		std::cout << "Gamepad controller informations : " << std::endl;
		std::cout << "Name : " << SDL_GameControllerName(_gamepad.get()) << std::endl << std::endl;
	}
}
