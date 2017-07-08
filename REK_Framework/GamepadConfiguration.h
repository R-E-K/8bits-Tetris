#pragma once
#include <SDL2/SDL.h>
#include <iostream>

namespace REKFramework
{
	class GamepadConfiguration
	{
	public:
		GamepadConfiguration();
		~GamepadConfiguration();
		void PlugGamepad();
		void UnplugGamepad();
	private:
		SDL_GameController* gamepad;
		void DisplayDebugInformations() const;
	};
}

