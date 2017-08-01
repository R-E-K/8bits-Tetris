#pragma once
#include "DrawTextService.h"
#include "SDLDeletersFunctor.h"

namespace REKFramework
{
	DrawTextService::DrawTextService()
	{
		defaultClr = { 255, 255, 255 };
	}

	DrawTextService::DrawTextService(SDL_Color defaultColor)
	{
		defaultClr = defaultColor;
	}

	DrawTextService::~DrawTextService()
	{

	}

	void DrawTextService::DrawText(std::string const& itemMenuName, int x, int y)
	{
		DrawTextWithSizeAndColor(itemMenuName, x, y, 24, defaultClr);
	}

	void DrawTextService::DrawTextWithSize(std::string const& itemMenuName, int x, int y, int textSize)
	{
		DrawTextWithSizeAndColor(itemMenuName, x, y, textSize, defaultClr);
	}

	void DrawTextService::DrawTextWithColor(std::string const& itemMenuName, int x, int y, SDL_Color& color)
	{
		DrawTextWithSizeAndColor(itemMenuName, x, y, 24, color);
	}

	void DrawTextService::DrawTextWithSizeAndColor(std::string const& itemMenuName, int x, int y, int textSize, SDL_Color& color)
	{
		auto fontMenu = std::unique_ptr<TTF_Font, SdlDeleter>(
			TTF_OpenFont("resources/fonts/Minecraft.ttf", textSize)
			,SdlDeleter()
			);

		auto textSurface = std::unique_ptr<SDL_Surface, SdlDeleter>(
			TTF_RenderText_Solid(fontMenu.get(), itemMenuName.c_str(), color)
			,SdlDeleter()
			);

		auto textTexture = std::unique_ptr<SDL_Texture, SdlDeleter>(
			SDL_CreateTextureFromSurface(SDLMainObjectsProvider::GetRendererRawPointer(), textSurface.get())
			,SdlDeleter()
			);

		int textureWidth, textureHeight;
		SDL_QueryTexture(textTexture.get(), nullptr, nullptr, &textureWidth, &textureHeight);

		SDL_Rect itemMenuPosition;
		itemMenuPosition.x = x;
		itemMenuPosition.y = y;
		itemMenuPosition.w = textureWidth;
		itemMenuPosition.h = textureHeight;

		SDL_RenderCopy(SDLMainObjectsProvider::GetRendererRawPointer(), textTexture.get(), nullptr, &itemMenuPosition);
	}
}
