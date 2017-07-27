#pragma once
#include "DrawTextService.h"

namespace REKFramework
{
	DrawTextService::DrawTextService()
	{
		defaultClr = { 255, 255, 255 };
	}

	DrawTextService::DrawTextService(SDL_Color* defaultColor)
	{

	}

	DrawTextService::~DrawTextService()
	{

	}

	void DrawTextService::DrawText(std::string const& itemMenuName, int x, int y)
	{
		DrawTextWithSizeAndColor(itemMenuName, x, y, 24, &defaultClr);
	}

	void DrawTextService::DrawTextWithSize(std::string const& itemMenuName, int x, int y, int textSize)
	{
		DrawTextWithSizeAndColor(itemMenuName, x, y, textSize, &defaultClr);
	}

	void DrawTextService::DrawTextWithColor(std::string const& itemMenuName, int x, int y, SDL_Color* color)
	{
		DrawTextWithSizeAndColor(itemMenuName, x, y, 24, color);
	}

	void DrawTextService::DrawTextWithSizeAndColor(std::string const& itemMenuName, int x, int y, int textSize, SDL_Color* color)
	{
		TTF_Font* fontMenu = TTF_OpenFont("resources/fonts/Minecraft.ttf", textSize);
		SDL_Surface* textSurface = TTF_RenderText_Solid(fontMenu, itemMenuName.c_str(), *color);
		SDL_Texture* textTexture = SDL_CreateTextureFromSurface(SDLMainObjectsProvider::GetRendererRawPointer(), textSurface);

		int textureWidth, textureHeight;
		SDL_QueryTexture(textTexture, nullptr, nullptr, &textureWidth, &textureHeight);

		SDL_Rect itemMenuPosition;
		itemMenuPosition.x = x;
		itemMenuPosition.y = y;
		itemMenuPosition.w = textureWidth;
		itemMenuPosition.h = textureHeight;

		SDL_RenderCopy(SDLMainObjectsProvider::GetRendererRawPointer(), textTexture, nullptr, &itemMenuPosition);

		SDL_FreeSurface(textSurface);
		SDL_DestroyTexture(textTexture);
		TTF_CloseFont(fontMenu);
	}
}
