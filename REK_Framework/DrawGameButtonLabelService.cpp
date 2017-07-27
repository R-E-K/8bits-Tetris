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

	void DrawGameButtonLabelService::DrawWithLabel(std::string const& imagePathFile, char* label, int x, int y) const
	{
		auto buttonImg = ImageLoader::GetImage(imagePathFile);
		auto buttonTexture = std::unique_ptr<SDL_Texture, SdlDeleter>(
			SDL_CreateTextureFromSurface(SDLMainObjectsProvider::GetRendererRawPointer(), buttonImg.get())
			, SdlDeleter()
			);

		SDL_Rect itemMenuPosition;
		itemMenuPosition.x = x;
		itemMenuPosition.y = y;
		itemMenuPosition.w = 32;
		itemMenuPosition.h = 32;

		SDL_RenderCopy(SDLMainObjectsProvider::GetRendererRawPointer(), buttonTexture.get(), nullptr, &itemMenuPosition);

		x = itemMenuPosition.x + 40;
		y = itemMenuPosition.y + 7;

		drawTextSrvc->DrawText(label, x, y);
	}
}
