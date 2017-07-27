#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <memory>
#include "SDLDeletersFunctor.h"
#include <string>

namespace REKFramework
{
	class ImageLoader
	{
	public:
		ImageLoader();
		~ImageLoader();

		static std::shared_ptr<SDL_Surface> GetImage(std::string const& pathfile);
	};
}

