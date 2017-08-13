#pragma once
#include <SDL2/SDL_ttf.h>
#include <string>
#include <memory>
#include "../core/SDLDeletersFunctor.h"
#include "../core/SDLMainObjectsProvider.h"

namespace REKFramework
{
	class DrawTextService
	{
	public:
		DrawTextService();
		DrawTextService(SDL_Color defaultColor);

		~DrawTextService();

		static void DrawTextWithColor(std::string const& text, int x, int y, SDL_Color color);
		static void DrawTextWithSizeAndColor(std::string const& text, int x, int y, int textSize, SDL_Color color);
	private:
		SDL_Color defaultClr;
	};
}
