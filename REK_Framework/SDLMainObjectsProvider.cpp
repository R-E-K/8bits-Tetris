#pragma once
#include "SDLMainObjectsProvider.h"

SDL_Renderer* SDLMainObjectsProvider::renderer;
SDL_Window* SDLMainObjectsProvider::window;


SDLMainObjectsProvider::SDLMainObjectsProvider()
{
}


SDLMainObjectsProvider::~SDLMainObjectsProvider()
{
}

SDL_Renderer* SDLMainObjectsProvider::GetRenderer()
{
	return renderer;
}

SDL_Window* SDLMainObjectsProvider::GetWindow()
{
	return window;
}
