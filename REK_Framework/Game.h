#pragma once
#include <SDL2/SDL.h>
#include "window.h"
#include "SDLMainObjectsProvider.h"
#include "ErrorMessageManager.h"
#include "InputManager.h"
#include "GamepadConfiguration.h"


namespace REKFramework
{
	class Game
	{
	public:
		Game();
		~Game();
		
		void Execute();
	private:
		SDL_Window* window;
		SDL_Renderer* renderer;

		GameContextManager* gameContextMngr;
		InputManager* inputMngr;

		GameMenu* gameMenu;

		void Loop(SDL_Event* e);
		bool Init();

		void SetSDLMainObjectsToProvider() const;

		void HandleGameMenu();
	};
}

