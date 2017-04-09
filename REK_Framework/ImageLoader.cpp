#pragma once
#include "ImageLoader.h"


ImageLoader::ImageLoader()
{
}


ImageLoader::~ImageLoader()
{
}

SDL_Surface* ImageLoader::GetImage(const char* pathfile)
{
	SDL_Surface* picture = IMG_Load(pathfile);

	// Set transparency
	SDL_SetColorKey(picture, SDL_TRUE, SDL_MapRGB(picture->format, 0xFF, 0x00, 0xFF));

	return picture;
}
