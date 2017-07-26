#pragma once
#include <SDL2/SDL.h>

// Functor wrapping SDL structs destruction
struct SdlDeleter
{
	void operator()(SDL_Renderer* p) const
	{
		//SDL_DestroyRenderer(p);
	}

	void operator()(SDL_Window* p) const
	{
		//SDL_DestroyWindow(p);
	}
};
