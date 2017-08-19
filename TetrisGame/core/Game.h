#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include "SDLDeletersFunctor.h"
#include "window.h"
#include "SDLMainObjectsProvider.h"
#include "ErrorMessageManager.h"
#include <memory>
#include "../input/InputManager.h"
#include "../sounds/SoundManager.h"
#include "../menu/GameMenu.h"
#include "../entities/Board.h"
#include "../entities/GameOverScreen.h"
#include "GameContextManager.h"
#include "GameConfiguration.h"


namespace REKTetrisGame
{
	class Game
	{
	public:
		Game();
		~Game();
		
		void Execute();
	private:
		std::shared_ptr<SDL_Window> _window;
		std::shared_ptr<SDL_Renderer> _renderer;

		std::shared_ptr<GameConfiguration> _gameConfiguration;
		std::shared_ptr<GameContextManager> _gameContextManager;
		std::unique_ptr<InputManager> _inputManager;
		std::shared_ptr<SoundManager> _soundManager;

		std::shared_ptr<GameMenu> _gameMenu;
		std::shared_ptr<Board> _boardGame;
		std::unique_ptr<GameOverScreen> _gameOverScreen;

		void Loop(SDL_Event& e);
		bool Init();

		void SetSDLMainObjectsToProvider() const;

		void HandleGameMenu();
	};
}

