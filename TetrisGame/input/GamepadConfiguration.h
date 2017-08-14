#pragma once
#include <SDL2/SDL.h>
#include <iostream>
#include <memory>
#include "../core/SDLDeletersFunctor.h"

namespace REKTetrisGame
{
	class GamepadConfiguration
	{
	public:
		GamepadConfiguration();
		~GamepadConfiguration();
		void PlugGamepad();
		void UnplugGamepad();

		bool IsGamepadPlugged() const;
	private:
		std::unique_ptr<SDL_GameController, SdlDeleter> gamepad;
		void DisplayDebugInformations() const;
	};
}

