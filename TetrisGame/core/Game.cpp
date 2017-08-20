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

		if (!AreAllAssetsExists())
		{
			ErrorMessageManager::WriteErrorMessageToMessageBox("All assets are not present in resources folder, you need to redownload the game. Application will be closed. END END END");
			isInitOk = false;
		}
		else
		{

			//Initialize SDL
			if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_GAMECONTROLLER) < 0)
			{
				ErrorMessageManager::WriteErrorMessageToMessageBox("SDL could not be initialized. Application will be closed.");
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
						ErrorMessageManager::WriteErrorMessageToMessageBox("Window could not be created. Application will be closed.");
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
							ErrorMessageManager::WriteErrorMessageToMessageBox("Renderer could not be created. Application will be closed.");
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
								ErrorMessageManager::WriteErrorMessageToMessageBox("Cannot hide mouse cursor. Application will be closed.");
								isInitOk = false;
							}
							else
							{
								_gameContextManager = std::make_shared<GameContextManager>();
								_inputManager = std::make_unique<InputManager>(_gameContextManager);


								// SDL_ttf
								if (TTF_Init() != 0)
								{
									ErrorMessageManager::WriteErrorMessageToMessageBox("Could not load SDL2_ttf. Application will be closed.");
									isInitOk = false;
								}
								else
								{
									_soundManager = std::make_shared<SoundManager>();
									if (_soundManager->Init() < 0)
									{
										ErrorMessageManager::WriteErrorMessageToMessageBox("Could not Init SDL2_Mixer with OGG format. Application will be closed.");
										isInitOk = false;
									}
									else
									{
										_soundManager->PlayMusic(AssetsFilePathConsts::Music, 4000);

										SetSDLMainObjectsToProvider();
									}
								}
							}
						}
					}
				}
			}
		}

		return isInitOk;
	}

	bool Game::AreAllAssetsExists()
	{
		std::vector<std::string> fileNames;
		fileNames.push_back(AssetsFilePathConsts::ConfigFile);
		fileNames.push_back(AssetsFilePathConsts::Font);
		fileNames.push_back(AssetsFilePathConsts::Music);
		fileNames.push_back(AssetsFilePathConsts::SoundMenuClick);
		fileNames.push_back(AssetsFilePathConsts::SoundMenuOver);
		fileNames.push_back(AssetsFilePathConsts::TetrominoBlue);
		fileNames.push_back(AssetsFilePathConsts::TetrominoBrown);
		fileNames.push_back(AssetsFilePathConsts::TetrominoGreen);
		fileNames.push_back(AssetsFilePathConsts::TetrominoOrange);
		fileNames.push_back(AssetsFilePathConsts::TetrominoPurple);
		fileNames.push_back(AssetsFilePathConsts::TetrominoRed);
		fileNames.push_back(AssetsFilePathConsts::TetrominoYellow);
		fileNames.push_back(KeyboardKeysFilePathConsts::EnterKey);
		fileNames.push_back(KeyboardKeysFilePathConsts::BackspaceKey);
		fileNames.push_back(GamepadButtonsFilePathConsts::AButton);
		fileNames.push_back(GamepadButtonsFilePathConsts::BButton);
		bool allAssetsExists = true;

		for (auto filename : fileNames)
		{
			if (!FileManager::IsFileExists(filename))
			{
				allAssetsExists = false;
				break;
			}
		}

		return allAssetsExists;
	}

	void Game::Run()
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
				_soundManager->PlaySound(AssetsFilePathConsts::SoundMenuClick, 1);
			}
			_gameMenu->Draw(_boardGame);
		}

		if (GameContextManager::CurrentGameContext == GameContextEnum::INGAME && _gameMenu != nullptr)
		{

			_gameMenu.reset();
			_soundManager->PlaySound(AssetsFilePathConsts::SoundMenuOver, 1);

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
