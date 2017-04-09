#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class ImageLoader
{
public:
	ImageLoader();
	~ImageLoader();

	static SDL_Surface* GetImage(const char* pathfile);
};

