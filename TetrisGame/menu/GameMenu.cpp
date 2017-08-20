#pragma once
#include "GameMenu.h"
#include "../core/GameContextManager.h"


namespace REKTetrisGame
{
	GameMenu::GameMenu(std::shared_ptr<SoundManager> soundManager
		, std::shared_ptr<GameConfiguration> gameConfiguration
		, std::shared_ptr<GamepadConfiguration> gamepadConfiguration)
	{
		_gameMenuItems.clear();
		_gameMenuItems[0] = GameMenuItemEnum::PLAY;
		_gameMenuItems[1] = GameMenuItemEnum::FULLSCREEN;
		_gameMenuItems[2] = GameMenuItemEnum::CREDITS;
		_gameMenuItems[3] = GameMenuItemEnum::QUITGAME;

		_gameMenuLevel = 0;

		_selectedItem = GameMenuItemEnum::PLAY;
		_selectedItemIndex = 0;

		_background = nullptr;

		_drawTextService = std::make_unique<DrawTextService>();
		_drawGameButtonLabelService = std::make_unique<DrawGameButtonLabelService>();

		_soundManager = soundManager;
		_gameConfiguration = gameConfiguration;
		_gamepadConfiguration = gamepadConfiguration;

		_backgroundPositionX = (SCREEN_WIDTH / 4);
		_backgroundPositionY = (SCREEN_HEIGHT / 8);
	}

	GameMenu::~GameMenu()
	{

	}

	void GameMenu::Draw(std::shared_ptr<Board> board)
	{
		if (_gameMenuLevel == 0)
		{
			DrawMainMenu(board);
		}
		else
		{
			switch (_selectedItem)
			{
			case GameMenuItemEnum::CREDITS:
				DrawCredits();
				break;
			}
		}
	}

	void GameMenu::NavigateDown()
	{
		if (_selectedItemIndex < _gameMenuItems.size() - 1 && _gameMenuLevel == 0)
		{
			_selectedItemIndex++;
			_selectedItem = _gameMenuItems[_selectedItemIndex];
			_soundManager->PlaySound(AssetsFilePathConsts::SoundMenuOver, 1);
		}
	}

	void GameMenu::NavigateUp()
	{
		if (_selectedItemIndex > 0 && _gameMenuLevel == 0)
		{
			_selectedItemIndex--;
			_selectedItem = _gameMenuItems[_selectedItemIndex];
			_soundManager->PlaySound(AssetsFilePathConsts::SoundMenuOver, 1);
		}
	}

	void GameMenu::SelectItemMenu()
	{
		switch (_selectedItem)
		{
		case GameMenuItemEnum::PLAY:
			break;
		case GameMenuItemEnum::FULLSCREEN:
			_gameConfiguration->ToggleFullscreenConfig();
			WindowConfiguration::ToggleFullScreen();
			break;
		case GameMenuItemEnum::CREDITS:
			_soundManager->PlaySound(AssetsFilePathConsts::SoundMenuOver, 1);
			_gameMenuLevel = 1;
			break;
		case GameMenuItemEnum::QUITGAME:
			SDL_Event quitGame;
			quitGame.type = SDL_QUIT;
			SDL_PushEvent(&quitGame);
			break;
		}
	}

	void GameMenu::MenuBack()
	{
		switch (_selectedItem)
		{
		case GameMenuItemEnum::PLAY:
		case GameMenuItemEnum::QUITGAME:
			break;
		case GameMenuItemEnum::CREDITS:
			_gameMenuLevel = 0;
			_soundManager->PlaySound(AssetsFilePathConsts::SoundMenuOver, 1);
			break;
		}
	}

	bool GameMenu::MustDestroyGameMenuOnSelect() const
	{
		return (_selectedItem == GameMenuItemEnum::PLAY || _selectedItem == GameMenuItemEnum::QUITGAME);
	}

	bool GameMenu::MustDestroyGameMenuOnBack(std::shared_ptr<Board> board) const
	{
		return _gameMenuLevel == 0 
			&& GameContextManager::CurrentGameContext != GameContextEnum::STARTED
			&& GameContextManager::CurrentGameContext != GameContextEnum::GAMEOVER
			&& board != nullptr && !board->IsGameOver();
	}

	GameMenuItemEnum GameMenu::GetLastItemMenuSelected() const
	{
		return _selectedItem;
	}

	std::shared_ptr<SDL_Texture> GameMenu::CreateBackground(SDL_Rect& gameMenuPosition)
	{
		gameMenuPosition.x = _backgroundPositionX;
		gameMenuPosition.y = _backgroundPositionY;
		gameMenuPosition.w = (SCREEN_WIDTH / 2);
		gameMenuPosition.h = (SCREEN_HEIGHT / 1.5);

		_backgroundTextureWidth = gameMenuPosition.w;
		_backgroundTextureHeight = gameMenuPosition.h;

		auto backgroundSurface = std::unique_ptr<SDL_Surface, SdlDeleter>(
			SDL_CreateRGBSurface(0, gameMenuPosition.w, gameMenuPosition.h, 32, 0, 0, 0, 0)
			, SdlDeleter()
			);

		SDL_FillRect(backgroundSurface.get(), nullptr, SDL_MapRGB(backgroundSurface->format, 0x00, 0x00, 0x00));

		auto background = std::shared_ptr<SDL_Texture>(
			SDL_CreateTextureFromSurface(SDLMainObjectsProvider::GetRendererRawPointer(), backgroundSurface.get())
			, SdlDeleter()
			);

		// Active Alpha Blending (Opacity) to "background" texture
		SDL_SetTextureBlendMode(background.get(), SDL_BLENDMODE_BLEND);
		SDL_SetTextureAlphaMod(background.get(), 0xAA);

		return background;
	}

	void GameMenu::DrawMainMenu(std::shared_ptr<Board> board)
	{
		SDL_Rect gameMenuPosition;
		_background = CreateBackground(gameMenuPosition);

		SDL_RenderCopy(SDLMainObjectsProvider::GetRendererRawPointer(), _background.get(), nullptr, &gameMenuPosition);

		DrawItemsMenu(board);
		AddValidButton();

		if (MustDestroyGameMenuOnBack(board))
		{
			AddBackButton();
		}
	}

	void GameMenu::DrawItemsMenu(std::shared_ptr<Board> board) const
	{
		int x = _backgroundPositionX + (_backgroundTextureWidth / 15);
		int y = _backgroundPositionY + (_backgroundTextureHeight / 15);

		if (board != nullptr && !board->IsGameOver())
		{
			DrawItemMenu("Resume", GameMenuItemEnum::PLAY, x, y);
		}
		else
		{
			DrawItemMenu("Play", GameMenuItemEnum::PLAY, x, y);
		}

		y += (_backgroundTextureHeight / 8);
		if (WindowConfiguration::IsFullScreen())
		{
			DrawItemMenu("Set  windowed", GameMenuItemEnum::FULLSCREEN, x, y);
		}
		else
		{
			DrawItemMenu("Set  fullscreen", GameMenuItemEnum::FULLSCREEN, x, y);
		}

		y += (_backgroundTextureHeight / 8);
		DrawItemMenu("Credits", GameMenuItemEnum::CREDITS, x, y);
		y += (_backgroundTextureHeight / 8);
		DrawItemMenu("Quit game", GameMenuItemEnum::QUITGAME, x, y);
	}

	void GameMenu::DrawItemMenu(std::string const& itemMenuName, GameMenuItemEnum gameMenuItem, int x, int y) const
	{
		SDL_Color textColorSelected;

		if (_selectedItem == gameMenuItem)
		{
			textColorSelected = { 255, 255, 0 };
		}
		else
		{
			textColorSelected = { 255, 255, 255 };
		}

		DrawTextService::DrawTextWithSizeAndColor(itemMenuName, x, y
			, (_backgroundTextureHeight / 15)
			, textColorSelected);
	}

	void GameMenu::DrawCredits()
	{
		SDL_Rect gameMenuPosition;
		_background = CreateBackground(gameMenuPosition);
		SDL_RenderCopy(SDLMainObjectsProvider::GetRendererRawPointer(), _background.get(), nullptr, &gameMenuPosition);

		int x = _backgroundPositionX + (_backgroundTextureWidth / 10);
		int y = _backgroundPositionY + (_backgroundTextureHeight / 10);


		DrawTextService::DrawTextWithSizeAndColor("Code, design, music", x, y
			, (_backgroundTextureHeight / 15)
			, { 255, 255, 255 });

		y += (_backgroundTextureHeight / 12);

		DrawTextService::DrawTextWithSizeAndColor("and sounds : REK", x, y
			, (_backgroundTextureHeight / 15)
			, { 255, 255, 255 });

		y += (_backgroundTextureHeight / 8);

		DrawTextService::DrawTextWithSizeAndColor("Font : Upheaval", x, y
			, (_backgroundTextureHeight / 15)
			, { 255, 255, 255 });

		y += (_backgroundTextureHeight / 12);

		DrawTextService::DrawTextWithSizeAndColor("by Brian Kent", x, y
			, (_backgroundTextureHeight / 15)
			, { 255, 255, 255 });

		y += (_backgroundTextureHeight / 8);

		DrawTextService::DrawTextWithSizeAndColor("Source code and more", x, y
			, (_backgroundTextureHeight / 15)
			, { 255, 255, 255 });

		y += (_backgroundTextureHeight / 12);

		DrawTextService::DrawTextWithSizeAndColor("infos on", x, y
			, (_backgroundTextureHeight / 15)
			, { 255, 255, 255 });

		y += (_backgroundTextureHeight / 12);

		DrawTextService::DrawTextWithSizeAndColor("github.com/R-E-K", x, y
			, (_backgroundTextureHeight / 15)
			, { 255, 255, 255 });

		AddBackButton();
	}

	void GameMenu::AddBackButton() const
	{

		int textureWidth, textureHeight;
		SDL_QueryTexture(_background.get(), nullptr, nullptr, &textureWidth, &textureHeight);
		int x = _backgroundPositionX + (_backgroundTextureWidth - (_backgroundTextureWidth / 3.5));
		int y = _backgroundPositionY + (_backgroundTextureHeight - (_backgroundTextureHeight / 8));

		_drawGameButtonLabelService->DrawWithLabel(
			(_gamepadConfiguration->IsGamepadPlugged()) ? GamepadButtonsFilePathConsts::BButton : KeyboardKeysFilePathConsts::BackspaceKey
			, "Back", x, y
			, (_backgroundTextureWidth / 16)
			, (_backgroundTextureHeight / 16));
	}

	void GameMenu::AddValidButton() const
	{
		int textureWidth, textureHeight;
		SDL_QueryTexture(_background.get(), nullptr, nullptr, &textureWidth, &textureHeight);
		int x = _backgroundPositionX + (_backgroundTextureWidth / 15);
		int y = _backgroundPositionY + (_backgroundTextureHeight - (_backgroundTextureHeight / 8));

		_drawGameButtonLabelService->DrawWithLabel(
			(_gamepadConfiguration->IsGamepadPlugged()) ? GamepadButtonsFilePathConsts::AButton : KeyboardKeysFilePathConsts::EnterKey
			, "Select", x, y
			, (_backgroundTextureWidth / 16)
			, (_backgroundTextureHeight / 16));
	}
}
