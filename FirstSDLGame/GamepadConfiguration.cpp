#pragma once
#include "GamepadConfiguration.h"


using namespace std;

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
		cout << "Game controller " << SDL_GameControllerName(gamepad) << "Removed" << endl << endl;
		SDL_GameControllerClose(gamepad);
		gamepad = nullptr;
	}
}

void GamepadConfiguration::DisplayDebugInformations() const
{
	cout << "Gamepad controller informations : " << endl;
	cout << "Name : " << SDL_GameControllerName(gamepad) << endl << endl;
}
