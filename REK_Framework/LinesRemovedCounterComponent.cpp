#include "LinesRemovedCounterComponent.h"

namespace REKFramework
{
	LinesRemovedCounterComponent::LinesRemovedCounterComponent()
	{
		_countLinesRemoved = 0;

		_backgroundTextureWidth = (SCREEN_HEIGHT * (20.0 / 100.0));
		_backgroundTextureHeight = (SCREEN_HEIGHT * (10.0 / 100.0));

		LoadTextures();
	}


	LinesRemovedCounterComponent::~LinesRemovedCounterComponent()
	{

	}

	void LinesRemovedCounterComponent::Draw() const
	{
		DrawBorder();
		DrawBackground();
		DrawTitle();
		DrawLinesRemovedCounter();
	}

	void LinesRemovedCounterComponent::AddNumberOfLinesRemovedToCounter(int nbLinesRemoved)
	{
		_countLinesRemoved += nbLinesRemoved;
	}

	int LinesRemovedCounterComponent::GetLinesRemovedCounter() const
	{
		return _countLinesRemoved;
	}

	void LinesRemovedCounterComponent::LoadTextures()
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

	void LinesRemovedCounterComponent::DrawBorder() const
	{
		SDL_Rect backgroundTilePosition;
		backgroundTilePosition.x = (SCREEN_WIDTH / 8) - EntitiesConsts::BORDER_THICKNESS;
		backgroundTilePosition.y = SCREEN_HEIGHT * (20.0 / 100.0) - EntitiesConsts::BORDER_THICKNESS; // Start at 20% from top
		backgroundTilePosition.w = _backgroundTextureWidth + (EntitiesConsts::BORDER_THICKNESS * 2);
		backgroundTilePosition.h = _backgroundTextureHeight + (EntitiesConsts::BORDER_THICKNESS * 2);

		SDL_RenderCopy(SDLMainObjectsProvider::GetRendererRawPointer()
			, _borderBackgroundTexture.get()
			, nullptr, &backgroundTilePosition);
	}

	void LinesRemovedCounterComponent::DrawBackground() const
	{
		SDL_Rect backgroundTilePosition;
		backgroundTilePosition.x = (SCREEN_WIDTH / 8);
		backgroundTilePosition.y = SCREEN_HEIGHT * (20.0 / 100.0); // Start at 20% from top
		backgroundTilePosition.w = _backgroundTextureWidth;
		backgroundTilePosition.h = _backgroundTextureHeight;

		SDL_RenderCopy(SDLMainObjectsProvider::GetRendererRawPointer()
			, _backgroundTexture.get()
			, nullptr, &backgroundTilePosition);
	}

	void LinesRemovedCounterComponent::DrawTitle() const
	{
		SDL_Color color = { 255, 255, 255 };

		DrawTextService::DrawTextWithSizeAndColor("Lines"
			, (SCREEN_WIDTH / 8) + (_backgroundTextureWidth * (5.0 / 100.0))
			, SCREEN_HEIGHT * (19.5 / 100.0) + (_backgroundTextureHeight * (5.0 / 100.0))
			, _backgroundTextureHeight * (50.0 / 100.0)
			, color);
	}

	void LinesRemovedCounterComponent::DrawLinesRemovedCounter() const
	{
		SDL_Color color = { 50, 50, 255 };

		DrawTextService::DrawTextWithSizeAndColor(std::to_string(_countLinesRemoved)
			, (SCREEN_WIDTH / 8) + (_backgroundTextureWidth * (66.0 / 100.0))
			, SCREEN_HEIGHT * (19.5 / 100.0) + (_backgroundTextureHeight * (50.0 / 100.0))
			, _backgroundTextureHeight * (50.0 / 100.0)
			, color);
	}
}
