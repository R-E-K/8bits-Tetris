#pragma once
#include "Game.h"

namespace REKTetrisGame
{
	Game::Game()
	{
		//The window we'll be rendering to
		_window = nullptr;

		// Engine renderer
		_renderer = nullptr;

		// The class who manage all input
		_inputManager = nullptr;

		// Handle the game behavior according to the context (In-game, Pause, Menu etc...)
		_gameContextManager = nullptr;

		// Manage all sounds
		_soundManager = nullptr;

		_gameMenu = nullptr;
		_boardGame = nullptr;
		_gameOverScreen = nullptr;

		_gameConfiguration = nullptr;
		
	}


	Game::~Game()
	{
		
	}

	void Game::Loop(SDL_Event& e)
	{
		bool quitGame = false;

		while (!quitGame)
		{
			SDL_RenderClear(_renderer.get());

			if (_inputManager != nullptr)
				_inputManager->CheckInput(e, quitGame);

			if (_boardGame != nullptr)
			{
				if (!_boardGame->IsGameOver())
				{
					_boardGame->Update();
				}

				_boardGame->Draw();
			}

			HandleGameMenu();

			// Handle Game Over
			if (_boardGame != nullptr)
			{
				if (_boardGame->IsGameOver() && GameContextManager::CurrentGameContext == GameContextEnum::INGAME)
				{
					GameContextManager::CurrentGameContext = GameContextEnum::GAMEOVER;
				}
			}

			if (GameContextManager::CurrentGameContext == GameContextEnum::GAMEOVER)
			{
				if (_gameOverScreen == nullptr)
				{
					auto gamepadConfig = _inputManager->GetGamepadConfiguration();
					_gameOverScreen = std::make_unique<GameOverScreen>(gamepadConfig);
				}
				
				_gameOverScreen->Draw();
			}

			//Update the surface
			//SDL_UpdateWindowSurface(_window); // software rendering : Not good
			SDL_RenderPresent(_renderer.get()); // GPU rendering : Good !

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
			_gameConfiguration = std::make_shared<GameConfiguration>();
			if (_gameConfiguration->IsConfigFileFound())
			{
				_window = std::shared_ptr<SDL_Window>(
					SDL_CreateWindow("Tetris", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, _gameConfiguration->GetFullscreenConfig())
					, SdlDeleter()
					);

				if (_window == nullptr)
				{
					ErrorMessageManager::WriteErrorMessageToConsole("Window could not be created! SDL_Error : ");
					isInitOk = false;
				}
				else
				{
					_renderer = std::shared_ptr<SDL_Renderer>(
						SDL_CreateRenderer(_window.get(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC)
						, SdlDeleter()
						);

					if (_renderer == nullptr)
					{
						ErrorMessageManager::WriteErrorMessageToConsole("Renderer could not be created! SDL_Error : ");
						isInitOk = false;
					}
					else
					{
						// Init screen with light grey all over the surface
						SDL_SetRenderDrawColor(_renderer.get(), 0x44, 0x87, 0xC5, SDL_ALPHA_OPAQUE);
						SDL_RenderSetLogicalSize(_renderer.get(), SCREEN_WIDTH, SCREEN_HEIGHT);

						// About mouse cursor
						if (SDL_ShowCursor(SDL_DISABLE) < 0)
						{
							ErrorMessageManager::WriteErrorMessageToConsole("Cannot hide mouse cursor! SDL_Error : ");
							isInitOk = false;
						}
						else
						{
							_gameContextManager = std::make_shared<GameContextManager>();
							_inputManager = std::make_unique<InputManager>(_gameContextManager);


							// SDL_ttf
							if (TTF_Init() != 0)
							{
								ErrorMessageManager::WriteErrorMessageToConsole("Could not load SDL_ttf, SDL_Error : ");
								isInitOk = false;
							}
							else
							{
								_soundManager = std::make_shared<SoundManager>();
								if (_soundManager->Init() < 0)
								{
									ErrorMessageManager::WriteErrorMessageToConsole("Could not Init SDL2_Mixer with OGG format, SDL_Error : ");
									isInitOk = false;
								}

								_soundManager->PlayMusic("resources/songs/Tetris_MIDI.ogg", 4000);

								SetSDLMainObjectsToProvider();
							}
						}
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
		SDLMainObjectsProvider::_renderer = _renderer;
		SDLMainObjectsProvider::_window = _window;
	}

	void Game::HandleGameMenu()
	{

		if (_gameContextManager != nullptr 
			&& (
				GameContextManager::CurrentGameContext == GameContextEnum::MENU
				|| GameContextManager::CurrentGameContext == GameContextEnum::STARTED
				))
		{
			if (_gameMenu == nullptr)
			{
				auto gamepadConfig = _inputManager->GetGamepadConfiguration();
				_gameMenu = std::make_shared<GameMenu>(_soundManager, _gameConfiguration, gamepadConfig);
				_gameContextManager->SetGameMenu(_gameMenu);
				_soundManager->PlaySound("resources/sounds/MenuClick.wav", 1);
			}
			_gameMenu->Draw(_boardGame);
		}

		if (GameContextManager::CurrentGameContext == GameContextEnum::INGAME && _gameMenu != nullptr)
		{

			_gameMenu.reset();
			_soundManager->PlaySound("resources/sounds/MenuOver.wav", 1);

			if (_boardGame != nullptr && _boardGame->IsGameOver())
			{
				// We leave menu after game over and restart a new game
				if (GameContextManager::CurrentGameContext == GameContextEnum::INGAME)
				{
					_boardGame.reset();
					_boardGame = nullptr;
					_boardGame = std::make_shared<Board>();
					_gameContextManager->SetBoardGame(_boardGame);
				}
			}
			else if (_boardGame == nullptr)
			{
				_boardGame = std::make_shared<Board>();
				_gameContextManager->SetBoardGame(_boardGame);
			}
		}
	}

}
