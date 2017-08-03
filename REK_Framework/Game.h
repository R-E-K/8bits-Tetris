#pragma once
#include <SDL2/SDL.h>
#include "window.h"
#include "SDLMainObjectsProvider.h"
#include "ErrorMessageManager.h"
#include "InputManager.h"
#include "GamepadConfiguration.h"
#include "SoundManager.h"
#include <memory>
#include "Board.h"


namespace REKFramework
{
	class Game
	{
	public:
		Game();
		~Game();
		
		void Execute();
	private:
		std::shared_ptr<SDL_Window> window;
		std::shared_ptr<SDL_Renderer> renderer;

		std::shared_ptr<GameContextManager> gameContextMngr;
		std::unique_ptr<InputManager> inputMngr;
		std::shared_ptr<SoundManager> soundMngr;

		std::shared_ptr<GameMenu> gameMenu;
		std::shared_ptr<Board> boardGame;

		void Loop(SDL_Event& e);
		bool Init();

		void SetSDLMainObjectsToProvider() const;

		void HandleGameMenu();
	};
}

