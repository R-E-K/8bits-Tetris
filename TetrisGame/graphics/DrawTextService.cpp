#pragma once
#include "DrawTextService.h"

namespace REKTetrisGame
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

	void DrawTextService::DrawTextWithColor(std::string const& text, int x, int y, SDL_Color color)
	{
		DrawTextWithSizeAndColor(text, x, y, 24, color);
	}

	void DrawTextService::DrawTextWithSizeAndColor(std::string const& text, int x, int y, int textSize, SDL_Color color)
	{
		auto fontMenu = std::unique_ptr<TTF_Font, SdlDeleter>(
			TTF_OpenFont("resources/fonts/upheavtt.ttf", textSize)
			,SdlDeleter()
			);

		auto textSurface = std::unique_ptr<SDL_Surface, SdlDeleter>(
			TTF_RenderText_Solid(fontMenu.get(), text.c_str(), color)
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
