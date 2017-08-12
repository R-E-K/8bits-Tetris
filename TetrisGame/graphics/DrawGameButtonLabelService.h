#pragma once
#include <SDL2/SDL.h>
#include "ImageLoader.h"
#include "DrawTextService.h"
#include <string>
#include "../core/SDLDeletersFunctor.h"
#include "../core/SDLMainObjectsProvider.h"

namespace REKFramework
{
	class DrawGameButtonLabelService
	{
	public:
		DrawGameButtonLabelService();
		~DrawGameButtonLabelService();

		void DrawWithLabel(std::string const& imagePathFile, std::string const& label, int x, int y, int width, int height) const;
	private:
		std::unique_ptr<DrawTextService> drawTextSrvc;
	};
}

