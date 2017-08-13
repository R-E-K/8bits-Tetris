#pragma once
#include "Game.h"

namespace REKTetrisGame
{
	Game::Game()
	{
		//The window we'll be rendering to
		window = nullptr;

		// Engine renderer
		renderer = nullptr;

		// The class who manage all input
		inputMngr = nullptr;

		// Handle the game behavior according to the context (In-game, Pause, Menu etc...)
		gameContextMngr = nullptr;

		// Manage all sounds
		soundMngr = nullptr;

		gameMenu = nullptr;
		boardGame = nullptr;
		_gameOverScreen = nullptr;
		
	}


	Game::~Game()
	{
		
	}

	void Game::Loop(SDL_Event& e)
	{
		bool quitGame = false;

		while (!quitGame)
		{
			SDL_RenderClear(renderer.get());

			if (inputMngr != nullptr)
				inputMngr->CheckInput(e, quitGame);

			if (boardGame != nullptr)
			{
				if (!boardGame->IsGameOver())
				{
					boardGame->Update();
				}

				boardGame->Draw();
			}

			HandleGameMenu();

			// Handle Game Over
			if (boardGame != nullptr)
			{
				if (boardGame->IsGameOver() && GameContextManager::CurrentGameContext == GameContextEnum::INGAME)
				{
					GameContextManager::CurrentGameContext = GameContextEnum::GAMEOVER;
				}
			}

			if (GameContextManager::CurrentGameContext == GameContextEnum::GAMEOVER)
			{
				if (_gameOverScreen == nullptr)
				{
					_gameOverScreen = std::make_unique<GameOverScreen>();
				}
				
				_gameOverScreen->Draw();
			}

			//Update the surface
			//SDL_UpdateWindowSurface(window); // software rendering : Not good
			SDL_RenderPresent(renderer.get()); // GPU rendering : Good !

		}
	}

	// Return true if no error
	bool Game::Init()
	{
		bool isInitOk = true;

		//Initialize SDL
		if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_GAMECONTROLLER) < 0)
		{
			ErrorMessageManager::WriteErrorMessageToConsole("SDL could not initialize! SDL_Error : ");
			isInitOk = false;
		}
		else
		{
			window = std::shared_ptr<SDL_Window>(
				SDL_CreateWindow("Tetris", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN)
				, SdlDeleter()
				);

			if (window == nullptr)
			{
				ErrorMessageManager::WriteErrorMessageToConsole("Window could not be created! SDL_Error : ");
				isInitOk = false;
			}
			else
			{
				renderer = std::shared_ptr<SDL_Renderer>(
					SDL_CreateRenderer(window.get(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC)
					, SdlDeleter()
					);

				if (renderer == nullptr)
				{
					ErrorMessageManager::WriteErrorMessageToConsole("Renderer could not be created! SDL_Error : ");
					isInitOk = false;
				}
				else
				{
					// Init screen with light grey all over the surface
					SDL_SetRenderDrawColor(renderer.get(), 0xCC, 0xCC, 0xCC, SDL_ALPHA_OPAQUE);

					gameContextMngr = std::make_shared<GameContextManager>();

					inputMngr = std::make_unique<InputManager>(gameContextMngr);


					// SDL_ttf
					if (TTF_Init() != 0)
					{
						ErrorMessageManager::WriteErrorMessageToConsole("Could not load SDL_ttf, SDL_Error : ");
						isInitOk = false;
					}
					else
					{
						soundMngr = std::make_shared<SoundManager>();
						if (soundMngr->Init() < 0)
						{
							ErrorMessageManager::WriteErrorMessageToConsole("Could not Init SDL2_Mixer with OGG format, SDL_Error : ");
							isInitOk = false;
						}

						soundMngr->PlayMusic("resources/songs/Disasterpeace_Forgotten.ogg", 2000);

						SetSDLMainObjectsToProvider();
					}
				}
			}
		}

		return isInitOk;
	}

	void Game::Execute()
	{
		if (Init())
		{
			SDL_Event e;
			Loop(e);
		}
	}

	void Game::SetSDLMainObjectsToProvider() const
	{
		SDLMainObjectsProvider::renderer = renderer;
		SDLMainObjectsProvider::window = window;
	}

	void Game::HandleGameMenu()
	{

		if (gameContextMngr != nullptr 
			&& (
				GameContextManager::CurrentGameContext == GameContextEnum::MENU
				|| GameContextManager::CurrentGameContext == GameContextEnum::STARTED
				))
		{
			if (gameMenu == nullptr)
			{
				gameMenu = std::make_shared<GameMenu>(soundMngr);
				gameContextMngr->SetGameMenu(gameMenu);
				soundMngr->PlaySound("resources/sounds/MenuClick.wav", 1);
			}
			gameMenu->Draw(boardGame);
		}

		if (GameContextManager::CurrentGameContext == GameContextEnum::INGAME && gameMenu != nullptr)
		{

			gameMenu.reset();
			soundMngr->PlaySound("resources/sounds/MenuOver.wav", 1);

			if (boardGame != nullptr && boardGame->IsGameOver())
			{
				// We leave menu after game over and restart a new game
				if (GameContextManager::CurrentGameContext == GameContextEnum::INGAME)
				{
					boardGame.reset();
					boardGame = nullptr;
					boardGame = std::make_shared<Board>();
					gameContextMngr->SetBoardGame(boardGame);
				}
			}
			else if (boardGame == nullptr)
			{
				boardGame = std::make_shared<Board>();
				gameContextMngr->SetBoardGame(boardGame);
			}
		}
	}

}
