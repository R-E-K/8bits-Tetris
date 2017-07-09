#pragma once
#include "Game.h"
#include <SDL2/SDL_mixer.h>

namespace REKFramework
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
	}


	Game::~Game()
	{
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		delete inputMngr;
		delete gameContextMngr;
		if (gameMenu != nullptr) delete gameMenu;

		//Quit SDL subsystems
		TTF_Quit();
		IMG_Quit();

		delete soundMngr;

		SDL_Quit();
	}

	void Game::Loop(SDL_Event* e)
	{
		bool quitGame = false;

		while (!quitGame)
		{
			SDL_RenderClear(renderer);

			HandleGameMenu();

			inputMngr->CheckInput(e, &quitGame);

			//Update the surface
			//SDL_UpdateWindowSurface(window); // software rendering : Not good
			SDL_RenderPresent(renderer); // GPU rendering : Good !

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
			window = SDL_CreateWindow("The best game ever !", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
				SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

			if (window == nullptr)
			{
				ErrorMessageManager::WriteErrorMessageToConsole("Window could not be created! SDL_Error : ");
				isInitOk = false;
			}
			else
			{
				renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

				if (renderer == nullptr)
				{
					ErrorMessageManager::WriteErrorMessageToConsole("Renderer could not be created! SDL_Error : ");
					isInitOk = false;
				}
				else
				{
					// Init screen with light grey all over the surface
					SDL_SetRenderDrawColor(renderer, 0xCC, 0xCC, 0xCC, SDL_ALPHA_OPAQUE);

					gameContextMngr = new GameContextManager();

					inputMngr = new InputManager(gameContextMngr);


					// SDL_ttf
					if (TTF_Init() != 0)
					{
						ErrorMessageManager::WriteErrorMessageToConsole("Could not load SDL_ttf, SDL_Error : ");
						isInitOk = false;
					}
					else
					{
						soundMngr = new SoundManager();
						if (soundMngr->Init() < 0)
						{
							ErrorMessageManager::WriteErrorMessageToConsole("Could not Init SDL2_Mixer with OGG format, SDL_Error : ");
							isInitOk = false;
						}

						soundMngr->LoadMusic("resources/songs/MUS_N_CD_1.ogg", 2000);

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
			Loop(&e);
		}
	}

	void Game::SetSDLMainObjectsToProvider() const
	{
		SDLMainObjectsProvider::renderer = renderer;
		SDLMainObjectsProvider::window = window;
	}

	void Game::HandleGameMenu()
	{
		if (gameContextMngr != nullptr && gameContextMngr->currentGameContext == MENU)
		{
			if (gameMenu == nullptr)
			{
				gameMenu = new GameMenu();
				gameContextMngr->SetGameMenu(gameMenu);
			}
			gameMenu->Draw();
		}

		if (gameContextMngr->currentGameContext == INGAME && gameMenu != nullptr)
		{
			delete gameMenu;
			gameMenu = nullptr;
		}
	}

}