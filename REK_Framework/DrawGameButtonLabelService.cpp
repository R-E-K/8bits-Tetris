#pragma once
#include "DrawGameButtonLabelService.h"
#include "SDLDeletersFunctor.h"

namespace REKFramework
{
	DrawGameButtonLabelService::DrawGameButtonLabelService()
	{
		drawTextSrvc = std::make_unique<DrawTextService>();
	}


	DrawGameButtonLabelService::~DrawGameButtonLabelService()
	{
		
	}

	void DrawGameButtonLabelService::DrawWithLabel(std::string const& imagePathFile, std::string const& label, int x, int y, int width, int height) const
	{
		auto buttonImg = ImageLoader::GetImage(imagePathFile);
		auto buttonTexture = std::unique_ptr<SDL_Texture, SdlDeleter>(
			SDL_CreateTextureFromSurface(SDLMainObjectsProvider::GetRendererRawPointer(), buttonImg.get())
			, SdlDeleter()
			);

		SDL_Rect itemMenuPosition;
		itemMenuPosition.x = x;
		itemMenuPosition.y = y;
		itemMenuPosition.w = height; // It's a square
		itemMenuPosition.h = height;

		SDL_RenderCopy(SDLMainObjectsProvider::GetRendererRawPointer(), buttonTexture.get(), nullptr, &itemMenuPosition);

		x = itemMenuPosition.x + height + (height / 4);

		DrawTextService::DrawTextWithSizeAndColor(label, x, y, height, { 255, 255, 255 });
	}
}
