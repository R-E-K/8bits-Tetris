#pragma once
#include <SDL2/SDL.h>
#include <iostream>
#include <memory>
#include "../core/SDLDeletersFunctor.h"

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
		std::unique_ptr<SDL_GameController, SdlDeleter> gamepad;
		void DisplayDebugInformations() const;
	};
}

