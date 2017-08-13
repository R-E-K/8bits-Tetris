#include "LevelComponent.h"

namespace REKTetrisGame
{
	LevelComponent::LevelComponent()
	{
		_level = 1;

		_backgroundTextureWidth = (SCREEN_HEIGHT * (20.0 / 100.0));
		_backgroundTextureHeight = (SCREEN_HEIGHT * (10.0 / 100.0));

		LoadTextures();
	}


	LevelComponent::~LevelComponent()
	{
		
	}

	void LevelComponent::Draw() const
	{
		DrawBorder();
		DrawBackground();
		DrawTitle();
		DrawLevelCounter();
	}

	void LevelComponent::DefineLevel(int nbTotalLinesRemoved)
	{
		_level = (nbTotalLinesRemoved / 10) + 1;

		// Level 10 is maximum
		if (_level > 10)
			_level = 10;
	}

	int LevelComponent::GetLevel() const
	{
		return _level;
	}

	void LevelComponent::LoadTextures()
	{
		auto darkLight = std::unique_ptr<SDL_Surface, SdlDeleter>(
			SDL_CreateRGBSurface(0, _backgroundTextureWidth, _backgroundTextureHeight, 32, 0, 0, 0, 0)
			, SdlDeleter());

		SDL_FillRect(darkLight.get(), nullptr, SDL_MapRGB(darkLight->format, 171, 171, 171));

		_backgroundTexture = std::unique_ptr<SDL_Texture, SdlDeleter>(
			SDL_CreateTextureFromSurface(SDLMainObjectsProvider::GetRendererRawPointer(), darkLight.get()),
			SdlDeleter()
			);

		auto surfaceBorder = std::unique_ptr<SDL_Surface, SdlDeleter>(
			SDL_CreateRGBSurface(0, _backgroundTextureWidth * EntitiesConsts::NB_COLUMNS, _backgroundTextureHeight, 32, 0, 0, 0, 0)
			, SdlDeleter());

		SDL_FillRect(surfaceBorder.get(), nullptr, SDL_MapRGB(surfaceBorder->format, 0, 0, 0));

		_borderBackgroundTexture = std::unique_ptr<SDL_Texture, SdlDeleter>(
			SDL_CreateTextureFromSurface(SDLMainObjectsProvider::GetRendererRawPointer(), surfaceBorder.get()),
			SdlDeleter()
			);
	}

	void LevelComponent::DrawBorder() const
	{
		SDL_Rect backgroundTilePosition;
		backgroundTilePosition.x = (SCREEN_WIDTH / 6) - EntitiesConsts::BORDER_THICKNESS;
		backgroundTilePosition.y = SCREEN_HEIGHT * (2.0 / 100.0) - EntitiesConsts::BORDER_THICKNESS; // Start at 2% from top
		backgroundTilePosition.w = _backgroundTextureWidth + (EntitiesConsts::BORDER_THICKNESS * 2);
		backgroundTilePosition.h = _backgroundTextureHeight + (EntitiesConsts::BORDER_THICKNESS * 2);

		SDL_RenderCopy(SDLMainObjectsProvider::GetRendererRawPointer()
			, _borderBackgroundTexture.get()
			, nullptr, &backgroundTilePosition);
	}

	void LevelComponent::DrawBackground() const
	{
		SDL_Rect backgroundTilePosition;
		backgroundTilePosition.x = (SCREEN_WIDTH / 6);
		backgroundTilePosition.y = SCREEN_HEIGHT * (2.0 / 100.0); // Start at 2% from top
		backgroundTilePosition.w = _backgroundTextureWidth;
		backgroundTilePosition.h = _backgroundTextureHeight;

		SDL_RenderCopy(SDLMainObjectsProvider::GetRendererRawPointer()
			, _backgroundTexture.get()
			, nullptr, &backgroundTilePosition);
	}

	void LevelComponent::DrawTitle() const
	{
		SDL_Color color = { 255, 255, 255 };

		DrawTextService::DrawTextWithSizeAndColor("Level"
			, (SCREEN_WIDTH / 6) + (_backgroundTextureWidth * (5.0 / 100.0))
			, SCREEN_HEIGHT * (1.5 / 100.0) + (_backgroundTextureHeight * (5.0 / 100.0))
			, _backgroundTextureHeight * (50.0 / 100.0)
			, color);
	}

	void LevelComponent::DrawLevelCounter() const
	{
		SDL_Color color = { 50, 50, 255 };

		DrawTextService::DrawTextWithSizeAndColor(std::to_string(_level)
			, (SCREEN_WIDTH / 6) + (_backgroundTextureWidth * (66.0 / 100.0))
			, SCREEN_HEIGHT * (1.5 / 100.0) + (_backgroundTextureHeight * (50.0 / 100.0))
			, _backgroundTextureHeight * (50.0 / 100.0)
			, color);
	}
}
