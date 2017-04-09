#pragma once
#include "DrawGameButtonLabelService.h"

DrawGameButtonLabelService::DrawGameButtonLabelService()
{
	drawTextSrvc = new DrawTextService();
}


DrawGameButtonLabelService::~DrawGameButtonLabelService()
{
	delete drawTextSrvc;
}

void DrawGameButtonLabelService::DrawWithLabel(const char* imagePathFile, char* label, int x, int y) const
{
	SDL_Surface* buttonImg = ImageLoader::GetImage(imagePathFile);
	SDL_Texture* buttonTexture = SDL_CreateTextureFromSurface(SDLMainObjectsProvider::GetRenderer(), buttonImg);

	SDL_Rect* itemMenuPosition = new SDL_Rect();
	itemMenuPosition->x = x;
	itemMenuPosition->y = y;
	itemMenuPosition->w = 32;
	itemMenuPosition->h = 32;

	SDL_RenderCopy(SDLMainObjectsProvider::GetRenderer(), buttonTexture, nullptr, itemMenuPosition);

	x = itemMenuPosition->x + 40;
	y = itemMenuPosition->y + 7;

	drawTextSrvc->DrawText(label, x, y);

	delete itemMenuPosition;
	SDL_FreeSurface(buttonImg);
	SDL_DestroyTexture(buttonTexture);
}
