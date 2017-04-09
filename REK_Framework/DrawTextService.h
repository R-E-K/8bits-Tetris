#pragma once
#include <SDL2/SDL_ttf.h>
#include "SDLMainObjectsProvider.h"

class DrawTextService
{
public:
	DrawTextService();
	DrawTextService(SDL_Color* defaultColor);

	~DrawTextService();

	void DrawText(const char* itemMenuName, int x, int y);
	void DrawTextWithSize(const char* itemMenuName, int x, int y, int textSize);
	void DrawTextWithColor(const char* itemMenuName, int x, int y, SDL_Color* color);
	void DrawTextWithSizeAndColor(const char* itemMenuName, int x, int y, int textSize, SDL_Color* color);
private:
	SDL_Color defaultClr;
};

