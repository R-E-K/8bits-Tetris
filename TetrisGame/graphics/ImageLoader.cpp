#pragma once
#include "ImageLoader.h"

namespace REKTetrisGame
{
	ImageLoader::ImageLoader()
	{
	}


	ImageLoader::~ImageLoader()
	{
	}

	std::unique_ptr<SDL_Surface, SdlDeleter> ImageLoader::GetImageWithoutTransparency(std::string const& pathfile)
	{
		auto picture = std::unique_ptr<SDL_Surface, SdlDeleter>(IMG_Load(pathfile.c_str()), SdlDeleter());

		return std::move(picture);
	}

	std::unique_ptr<SDL_Surface, SdlDeleter> ImageLoader::GetImage(std::string const& pathfile)
	{
		auto picture = std::unique_ptr<SDL_Surface, SdlDeleter>(IMG_Load(pathfile.c_str()), SdlDeleter());

		// Set transparency
		SDL_SetColorKey(picture.get(), SDL_TRUE, SDL_MapRGB(picture->format, 0xFF, 0x00, 0xFF));

		return std::move(picture);
	}

	std::unique_ptr<SDL_Surface, SdlDeleter> ImageLoader::GetImage(std::string const& pathfile, SDL_Color transparentColor)
	{
		auto picture = std::unique_ptr<SDL_Surface, SdlDeleter>(IMG_Load(pathfile.c_str()), SdlDeleter());

		// Set transparency
		SDL_SetColorKey(picture.get(), SDL_TRUE, SDL_MapRGB(picture->format, transparentColor.r, transparentColor.g, transparentColor.b));

		return std::move(picture);
	}
}
