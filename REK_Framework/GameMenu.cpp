#pragma once
#include "GameMenu.h"


namespace REKFramework
{
	GameMenu::GameMenu()
	{
		gameMenuItems.clear();
		gameMenuItems[0] = GameMenuItem::PLAY;
		gameMenuItems[1] = GameMenuItem::CREDITS;
		gameMenuItems[2] = GameMenuItem::QUITGAME;

		GameMenuLevel = 0;

		selectedItem = GameMenuItem::PLAY;
		selectedItemIndex = 0;

		background = nullptr;

		drawTextSrvc = std::make_unique<DrawTextService>();
		DrawGameButtonLabelSrvc = std::make_unique<DrawGameButtonLabelService>();

		backgroundPositionX = (SCREEN_WIDTH / 4);
		backgroundPositionY = (SCREEN_HEIGHT / 8);
	}

	GameMenu::~GameMenu()
	{

	}

	void GameMenu::Draw()
	{
		if (GameMenuLevel == 0)
		{
			DrawMainMenu();
		}
		else
		{
			switch (selectedItem)
			{
			case GameMenuItem::CREDITS:
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
		}
	}

	void GameMenu::NavigateUp()
	{
		if (selectedItemIndex > 0 && GameMenuLevel == 0)
		{
			selectedItemIndex--;
			selectedItem = gameMenuItems[selectedItemIndex];
		}
	}

	void GameMenu::SelectItemMenu()
	{
		switch (selectedItem)
		{
		case GameMenuItem::PLAY:
			break;
		case GameMenuItem::CREDITS:
			GameMenuLevel = 1;
			break;
		case GameMenuItem::QUITGAME:
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
		case GameMenuItem::PLAY:
		case GameMenuItem::QUITGAME:
			break;
		case GameMenuItem::CREDITS:
			GameMenuLevel = 0;
			break;
		}
	}

	bool GameMenu::MustDestroyGameMenuOnSelect() const
	{
		return (selectedItem == GameMenuItem::PLAY || selectedItem == GameMenuItem::QUITGAME);
	}

	bool GameMenu::MustDestroyGameMenuOnBack() const
	{
		return GameMenuLevel == 0;
	}

	std::shared_ptr<SDL_Texture> GameMenu::CreateBackground(SDL_Rect& gameMenuPosition) const
	{
		gameMenuPosition.x = backgroundPositionX;
		gameMenuPosition.y = backgroundPositionY;
		gameMenuPosition.w = (SCREEN_WIDTH / 2);
		gameMenuPosition.h = (SCREEN_HEIGHT / 1.5);

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

	void GameMenu::DrawMainMenu()
	{
		SDL_Rect gameMenuPosition;
		background = CreateBackground(gameMenuPosition);

		SDL_RenderCopy(SDLMainObjectsProvider::GetRendererRawPointer(), background.get(), nullptr, &gameMenuPosition);

		DrawItemsMenu();
		AddValidButton();
		AddBackButton();
	}

	void GameMenu::DrawItemsMenu() const
	{
		int x = backgroundPositionX + 20;
		int y = backgroundPositionY + 20;

		DrawItemMenu("Play", GameMenuItem::PLAY, x, y);
		y += 40;
		DrawItemMenu("Credits", GameMenuItem::CREDITS, x, y);
		y += 40;
		DrawItemMenu("Quit game", GameMenuItem::QUITGAME, x, y);
	}

	void GameMenu::DrawItemMenu(std::string const& itemMenuName, GameMenuItem gameMenuItem, int x, int y) const
	{
		SDL_Color textColorSelected = { 255, 255, 0 };

		if (selectedItem == gameMenuItem)
		{
			drawTextSrvc->DrawTextWithColor(itemMenuName, x, y, textColorSelected);
		}
		else
		{
			drawTextSrvc->DrawText(itemMenuName, x, y);
		}
	}

	void GameMenu::DrawCredits()
	{
		SDL_Rect gameMenuPosition;
		background = CreateBackground(gameMenuPosition);
		SDL_RenderCopy(SDLMainObjectsProvider::GetRendererRawPointer(), background.get(), nullptr, &gameMenuPosition);

		int x = backgroundPositionX + 40;
		int y = backgroundPositionY + 40;

		drawTextSrvc->DrawText("Game made by", x, y);

		y += 50;

		drawTextSrvc->DrawTextWithSize("REK", x, y, 72);

		AddBackButton();
	}

	void GameMenu::AddBackButton() const
	{
		int textureWidth, textureHeight;
		SDL_QueryTexture(background.get(), nullptr, nullptr, &textureWidth, &textureHeight);
		int x = backgroundPositionX + (textureWidth - (textureWidth / 3.5));
		int y = backgroundPositionY + (textureHeight - (textureHeight / 8));

		DrawGameButtonLabelSrvc->DrawWithLabel(GamepadButtonsFilePathConsts::BButton, "Back", x, y);
	}

	void GameMenu::AddValidButton() const
	{
		int textureWidth, textureHeight;
		SDL_QueryTexture(background.get(), nullptr, nullptr, &textureWidth, &textureHeight);
		int x = backgroundPositionX + 5;
		int y = backgroundPositionY + (textureHeight - (textureHeight / 8));

		DrawGameButtonLabelSrvc->DrawWithLabel(GamepadButtonsFilePathConsts::AButton, "Select", x, y);
	}
}