#pragma once
#include <SDL2/SDL.h>
#include "SDLMainObjectsProvider.h"
#include "ImageLoader.h"
#include "DrawTextService.h"
#include <string>

namespace REKFramework
{
	class DrawGameButtonLabelService
	{
	public:
		DrawGameButtonLabelService();
		~DrawGameButtonLabelService();

		void DrawWithLabel(std::string const& imagePathFile, char* label, int x, int y) const;
	private:
		std::unique_ptr<DrawTextService> drawTextSrvc;
	};
}

