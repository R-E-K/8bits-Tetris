#pragma once
#include <SDL2/SDL_ttf.h>
#include "SDLMainObjectsProvider.h"
#include <string>

namespace REKFramework
{
	class DrawTextService
	{
	public:
		DrawTextService();
		DrawTextService(SDL_Color* defaultColor);

		~DrawTextService();

		void DrawText(std::string const& itemMenuName, int x, int y);
		void DrawTextWithSize(std::string const& itemMenuName, int x, int y, int textSize);
		void DrawTextWithColor(std::string const& itemMenuName, int x, int y, SDL_Color* color);
		void DrawTextWithSizeAndColor(std::string const& itemMenuName, int x, int y, int textSize, SDL_Color* color);
	private:
		SDL_Color defaultClr;
	};
}
