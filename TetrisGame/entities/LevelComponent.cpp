#include "LevelComponent.h"

namespace REKTetrisGame
{
	LevelComponent::LevelComponent(double widthPercent, double HeightPercent)
		: Component(widthPercent, HeightPercent)
	{
		Component::LoadTextures();
		_level = 1;
	}

	LevelComponent::~LevelComponent()
	{
		
	}

	void LevelComponent::Draw() const
	{
		Component::Draw();
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
			, (SCREEN_WIDTH / 6) + (_backgroundTextureWidth * (50.0 / 100.0))
			, SCREEN_HEIGHT * (1.5 / 100.0) + (_backgroundTextureHeight * (50.0 / 100.0))
			, _backgroundTextureHeight * (50.0 / 100.0)
			, color);
	}
}
