#pragma once
#include "SDLMainObjectsProvider.h"

namespace REKFramework
{
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
}
