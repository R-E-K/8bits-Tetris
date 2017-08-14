#include "Component.h"

namespace REKTetrisGame
{
	Component::Component(double widthPercent, double HeightPercent)
	{
		_backgroundTextureWidth = (SCREEN_HEIGHT * (widthPercent / 100.0));
		_backgroundTextureHeight = (SCREEN_HEIGHT * (HeightPercent / 100.0));
	}


	Component::~Component()
	{
	}

	void Component::Draw() const
	{
		DrawBorder();
		DrawBackground();
		DrawTitle();
	}

	void Component::LoadTextures()
	{
		auto darkLight = std::unique_ptr<SDL_Surface, SdlDeleter>(
			SDL_CreateRGBSurface(0, _backgroundTextureWidth, _backgroundTextureHeight, 32, 0, 0, 0, 0)
			, SdlDeleter());

		SDL_FillRect(darkLight.get(), nullptr, SDL_MapRGB(darkLight->format, 0x86, 0xA6, 0xC3));

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

	void Component::DrawBorder() const
	{
	}

	void Component::DrawBackground() const
	{
	}

	void Component::DrawTitle() const
	{
	}
}
