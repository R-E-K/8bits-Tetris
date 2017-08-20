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

		static std::unique_ptr<SDL_Surface, SdlDeleter> GetImage(std::string const& pathfile);
		static std::unique_ptr<SDL_Surface, SdlDeleter> ImageLoader::GetImage(std::string const& pathfile, SDL_Color transparentColor);
		static std::unique_ptr<SDL_Surface, SdlDeleter> ImageLoader::GetImageWithoutTransparency(std::string const& pathfile);
	};
}

