#pragma once
#include "ImageLoader.h"

namespace REKFramework
{
	ImageLoader::ImageLoader()
	{
	}


	ImageLoader::~ImageLoader()
	{
	}

	std::shared_ptr<SDL_Surface> ImageLoader::GetImage(std::string const& pathfile)
	{
		auto picture = std::shared_ptr<SDL_Surface>(IMG_Load(pathfile.c_str()), SdlDeleter());

		// Set transparency
		SDL_SetColorKey(picture.get(), SDL_TRUE, SDL_MapRGB(picture->format, 0xFF, 0x00, 0xFF));

		return picture;
	}
}
