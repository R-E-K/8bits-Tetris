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
		DrawTextService(SDL_Color defaultColor);

		~DrawTextService();

		void DrawText(std::string const& text, int x, int y) const;
		void DrawTextWithSize(std::string const& text, int x, int y, int textSize) const;
		static void DrawTextWithColor(std::string const& text, int x, int y, SDL_Color color);
		static void DrawTextWithSizeAndColor(std::string const& text, int x, int y, int textSize, SDL_Color color);
	private:
		SDL_Color defaultClr;
	};
}
