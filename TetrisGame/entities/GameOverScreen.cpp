#include "GameOverScreen.h"

namespace REKTetrisGame
{
	GameOverScreen::GameOverScreen()
	{
		_backgroundTextureRect.w = SCREEN_WIDTH / 1.5;
		_backgroundTextureRect.h = SCREEN_HEIGHT / 3;
		_backgroundTextureRect.x = (SCREEN_WIDTH / 6); //- (_backgroundTextureRect.w * 2);
		_backgroundTextureRect.y = (SCREEN_HEIGHT / 6); // -(_backgroundTextureRect.h * 4);

		LoadTextures();
	}


	GameOverScreen::~GameOverScreen()
	{
	}

	void GameOverScreen::Draw() const
	{
		DrawBackground();
		DrawText();
	}

	void GameOverScreen::LoadTextures()
	{
		auto backgroundSurface = std::unique_ptr<SDL_Surface, SdlDeleter>(
			SDL_CreateRGBSurface(0, _backgroundTextureRect.w, _backgroundTextureRect.h, 32, 0, 0, 0, 0)
			, SdlDeleter()
			);

		SDL_FillRect(backgroundSurface.get(), nullptr, SDL_MapRGB(backgroundSurface->format, 0xFF, 0x00, 0x00));

		_backgroundTexture = std::unique_ptr<SDL_Texture, SdlDeleter>(
			SDL_CreateTextureFromSurface(SDLMainObjectsProvider::GetRendererRawPointer(), backgroundSurface.get())
			, SdlDeleter()
			);

		// Active Alpha Blending (Opacity) to "background" texture
		SDL_SetTextureBlendMode(_backgroundTexture.get(), SDL_BLENDMODE_BLEND);
		SDL_SetTextureAlphaMod(_backgroundTexture.get(), 0xAA);
	}

	void GameOverScreen::DrawBackground() const
	{
		SDL_RenderCopy(SDLMainObjectsProvider::GetRendererRawPointer()
			, _backgroundTexture.get()
			, nullptr, &_backgroundTextureRect);
	}

	void GameOverScreen::DrawText() const
	{
		SDL_Color color = { 255, 255, 255 };

		DrawTextService::DrawTextWithSizeAndColor("Game Over"
			, _backgroundTextureRect.x + (_backgroundTextureRect.w * (5.0 / 100.0))
			, _backgroundTextureRect.y + (_backgroundTextureRect.h * (5.0 / 100.0))
			, _backgroundTextureRect.h * (50.0 / 100.0)
			, color);

		DrawTextService::DrawTextWithSizeAndColor("Press Start to continue"
			, _backgroundTextureRect.x + (_backgroundTextureRect.w * (5.0 / 100.0))
			, _backgroundTextureRect.y + (_backgroundTextureRect.h * (60.0 / 100.0))
			, _backgroundTextureRect.h * (20.0 / 100.0)
			, color);
	}
}
