#pragma once
#include "GameMenu.h"
#include "../core/GameContextManager.h"


namespace REKTetrisGame
{
	GameMenu::GameMenu(std::shared_ptr<SoundManager> soundManager)
	{
		gameMenuItems.clear();
		gameMenuItems[0] = GameMenuItemEnum::PLAY;
		gameMenuItems[1] = GameMenuItemEnum::FULLSCREEN;
		gameMenuItems[2] = GameMenuItemEnum::CREDITS;
		gameMenuItems[3] = GameMenuItemEnum::QUITGAME;

		GameMenuLevel = 0;

		selectedItem = GameMenuItemEnum::PLAY;
		selectedItemIndex = 0;

		background = nullptr;

		drawTextSrvc = std::make_unique<DrawTextService>();
		DrawGameButtonLabelSrvc = std::make_unique<DrawGameButtonLabelService>();

		soundMngr = soundManager;

		backgroundPositionX = (SCREEN_WIDTH / 4);
		backgroundPositionY = (SCREEN_HEIGHT / 8);
	}

	GameMenu::~GameMenu()
	{

	}

	void GameMenu::Draw(std::shared_ptr<Board> board)
	{
		if (GameMenuLevel == 0)
		{
			DrawMainMenu(board);
		}
		else
		{
			switch (selectedItem)
			{
			case GameMenuItemEnum::CREDITS:
				DrawCredits();
				break;
			}
		}
	}

	void GameMenu::NavigateDown()
	{
		if (selectedItemIndex < gameMenuItems.size() - 1 && GameMenuLevel == 0)
		{
			selectedItemIndex++;
			selectedItem = gameMenuItems[selectedItemIndex];
			soundMngr->PlaySound("resources/sounds/MenuOver.wav", 1);
		}
	}

	void GameMenu::NavigateUp()
	{
		if (selectedItemIndex > 0 && GameMenuLevel == 0)
		{
			selectedItemIndex--;
			selectedItem = gameMenuItems[selectedItemIndex];
			soundMngr->PlaySound("resources/sounds/MenuOver.wav", 1);
		}
	}

	void GameMenu::SelectItemMenu()
	{
		switch (selectedItem)
		{
		case GameMenuItemEnum::PLAY:
			break;
		case GameMenuItemEnum::FULLSCREEN:
			WindowConfiguration::ToggleFullScreen();
			break;
		case GameMenuItemEnum::CREDITS:
			soundMngr->PlaySound("resources/sounds/MenuOver.wav", 1);
			GameMenuLevel = 1;
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
		switch (selectedItem)
		{
		case GameMenuItemEnum::PLAY:
		case GameMenuItemEnum::QUITGAME:
			break;
		case GameMenuItemEnum::CREDITS:
			GameMenuLevel = 0;
			soundMngr->PlaySound("resources/sounds/MenuOver.wav", 1);
			break;
		}
	}

	bool GameMenu::MustDestroyGameMenuOnSelect() const
	{
		return (selectedItem == GameMenuItemEnum::PLAY || selectedItem == GameMenuItemEnum::QUITGAME);
	}

	bool GameMenu::MustDestroyGameMenuOnBack(std::shared_ptr<Board> board) const
	{
		return GameMenuLevel == 0 
			&& GameContextManager::CurrentGameContext != GameContextEnum::STARTED
			&& GameContextManager::CurrentGameContext != GameContextEnum::GAMEOVER
			&& board != nullptr && !board->IsGameOver();
	}

	GameMenuItemEnum GameMenu::GetLastItemMenuSelected() const
	{
		return selectedItem;
	}

	std::shared_ptr<SDL_Texture> GameMenu::CreateBackground(SDL_Rect& gameMenuPosition)
	{
		gameMenuPosition.x = backgroundPositionX;
		gameMenuPosition.y = backgroundPositionY;
		gameMenuPosition.w = (SCREEN_WIDTH / 2);
		gameMenuPosition.h = (SCREEN_HEIGHT / 1.5);

		backgroundTextureWidth = gameMenuPosition.w;
		backgroundTextureHeight = gameMenuPosition.h;

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
		background = CreateBackground(gameMenuPosition);

		SDL_RenderCopy(SDLMainObjectsProvider::GetRendererRawPointer(), background.get(), nullptr, &gameMenuPosition);

		DrawItemsMenu(board);
		AddValidButton();

		if (MustDestroyGameMenuOnBack(board))
		{
			AddBackButton();
		}
	}

	void GameMenu::DrawItemsMenu(std::shared_ptr<Board> board) const
	{
		int x = backgroundPositionX + (backgroundTextureWidth / 15);
		int y = backgroundPositionY + (backgroundTextureHeight / 15);

		if (board != nullptr && !board->IsGameOver())
		{
			DrawItemMenu("Resume", GameMenuItemEnum::PLAY, x, y);
		}
		else
		{
			DrawItemMenu("Play", GameMenuItemEnum::PLAY, x, y);
		}

		y += (backgroundTextureHeight / 8);
		if (WindowConfiguration::IsFullScreen())
		{
			DrawItemMenu("Set  windowed", GameMenuItemEnum::FULLSCREEN, x, y);
		}
		else
		{
			DrawItemMenu("Set  fullscreen", GameMenuItemEnum::FULLSCREEN, x, y);
		}

		y += (backgroundTextureHeight / 8);
		DrawItemMenu("Credits", GameMenuItemEnum::CREDITS, x, y);
		y += (backgroundTextureHeight / 8);
		DrawItemMenu("Quit game", GameMenuItemEnum::QUITGAME, x, y);
	}

	void GameMenu::DrawItemMenu(std::string const& itemMenuName, GameMenuItemEnum gameMenuItem, int x, int y) const
	{
		SDL_Color textColorSelected;

		if (selectedItem == gameMenuItem)
		{
			textColorSelected = { 255, 255, 0 };
		}
		else
		{
			textColorSelected = { 255, 255, 255 };
		}

		DrawTextService::DrawTextWithSizeAndColor(itemMenuName, x, y
			, (backgroundTextureHeight / 15)
			, textColorSelected);
	}

	void GameMenu::DrawCredits()
	{
		SDL_Rect gameMenuPosition;
		background = CreateBackground(gameMenuPosition);
		SDL_RenderCopy(SDLMainObjectsProvider::GetRendererRawPointer(), background.get(), nullptr, &gameMenuPosition);

		int x = backgroundPositionX + (backgroundTextureWidth / 10);
		int y = backgroundPositionY + (backgroundTextureHeight / 10);


		DrawTextService::DrawTextWithSizeAndColor("Game made by", x, y
			, (backgroundTextureHeight / 10)
			, { 255, 255, 255 });

		y += (backgroundTextureHeight / 4);

		DrawTextService::DrawTextWithSizeAndColor("REK", x, y
			, (backgroundTextureHeight / 5)
			, { 255, 255, 255 });

		AddBackButton();
	}

	void GameMenu::AddBackButton() const
	{

		int textureWidth, textureHeight;
		SDL_QueryTexture(background.get(), nullptr, nullptr, &textureWidth, &textureHeight);
		int x = backgroundPositionX + (backgroundTextureWidth - (backgroundTextureWidth / 3.5));
		int y = backgroundPositionY + (backgroundTextureHeight - (backgroundTextureHeight / 8));

		DrawGameButtonLabelSrvc->DrawWithLabel(GamepadButtonsFilePathConsts::BButton, "Back", x, y
			, (backgroundTextureWidth / 18)
			, (backgroundTextureHeight / 18));
	}

	void GameMenu::AddValidButton() const
	{
		int textureWidth, textureHeight;
		SDL_QueryTexture(background.get(), nullptr, nullptr, &textureWidth, &textureHeight);
		int x = backgroundPositionX + (backgroundTextureWidth / 15);
		int y = backgroundPositionY + (backgroundTextureHeight - (backgroundTextureHeight / 8));

		DrawGameButtonLabelSrvc->DrawWithLabel(GamepadButtonsFilePathConsts::AButton, "Select", x, y
			, (backgroundTextureWidth / 18)
			, (backgroundTextureHeight / 18));
	}
}
