#include "Board.h"
#include "SDLDeletersFunctor.h"
#include "window.h"
#include "SDLMainObjectsProvider.h"

namespace REKFramework
{
	Board::Board()
	{
		// It will be a square
		backgroundTextureWidth = (SCREEN_HEIGHT * (85.0 / 100.0)) / NB_ROWS;
		backgroundTextureHeight = (SCREEN_HEIGHT * (85.0 / 100.0)) / NB_ROWS;

		SetTexturesBackground();
	}


	Board::~Board()
	{
	}

	void Board::SetTexturesBackground()
	{
		auto surfaceLight = std::unique_ptr<SDL_Surface, SdlDeleter>(
			SDL_CreateRGBSurface(0, backgroundTextureWidth, backgroundTextureHeight, 32, 0, 0, 0, 0)
			, SdlDeleter());

		SDL_FillRect(surfaceLight.get(), nullptr, SDL_MapRGB(surfaceLight->format, 215, 215, 215));

		lightBackgroundTexture = std::shared_ptr<SDL_Texture>(
			SDL_CreateTextureFromSurface(SDLMainObjectsProvider::GetRendererRawPointer(), surfaceLight.get()),
			SdlDeleter()
			);


		auto darkLight = std::unique_ptr<SDL_Surface, SdlDeleter>(
			SDL_CreateRGBSurface(0, backgroundTextureWidth, backgroundTextureHeight, 32, 0, 0, 0, 0)
			, SdlDeleter());

		SDL_FillRect(darkLight.get(), nullptr, SDL_MapRGB(darkLight->format, 171, 171, 171));

		darkBackgroundTexture = std::shared_ptr<SDL_Texture>(
			SDL_CreateTextureFromSurface(SDLMainObjectsProvider::GetRendererRawPointer(), darkLight.get()),
			SdlDeleter()
			);
	}

	void Board::DrawBackground() const
	{
		int backgroundTileXInitPosition = SCREEN_WIDTH * (10.0 / 100.0);

		SDL_Rect backgroundTilePosition;
		backgroundTilePosition.x = backgroundTileXInitPosition;
		backgroundTilePosition.y = SCREEN_HEIGHT * (2.0 / 100.0) - backgroundTextureHeight; // Start at 2% from top
		backgroundTilePosition.w = backgroundTextureWidth;
		backgroundTilePosition.h = backgroundTextureHeight;

		bool isLight;

		for (int i = 0; i < NB_ROWS; i++)
		{
			backgroundTilePosition.y += backgroundTextureHeight;
			backgroundTilePosition.x = backgroundTileXInitPosition;

			// First column is always light
			isLight = true;
			for (int j = 0; j < NB_COLUMNS; j++)
			{
				backgroundTilePosition.x += backgroundTextureWidth;

				SDL_RenderCopy(SDLMainObjectsProvider::GetRendererRawPointer()
					, isLight ? lightBackgroundTexture.get() : darkBackgroundTexture.get()
					, nullptr, &backgroundTilePosition);

				isLight = !isLight;
			}
		}
	}
}