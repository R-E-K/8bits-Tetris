#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <memory>
#include "../core/SDLDeletersFunctor.h"
#include <string>

namespace REKTetrisGame
{
	class ImageLoader
	{
	public:
		ImageLoader();
		~ImageLoader();

		static std::shared_ptr<SDL_Surface> GetImage(std::string const& pathfile);
		static std::shared_ptr<SDL_Surface> ImageLoader::GetImage(std::string const& pathfile, SDL_Color transparentColor);
		static std::shared_ptr<SDL_Surface> ImageLoader::GetImageWithoutTransparency(std::string const& pathfile);
	};
}

