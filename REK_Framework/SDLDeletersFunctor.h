#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

// Functor wrapping SDL structs destruction
struct SdlDeleter
{
	void operator()(SDL_Window* p) const
	{
		SDL_DestroyWindow(p);
	}

	void operator()(SDL_Renderer* p) const
	{
		SDL_DestroyRenderer(p);
	}

	void operator()(SDL_Texture* p) const
	{
		SDL_DestroyTexture(p);
	}

	void operator()(SDL_Surface* p) const
	{
		SDL_FreeSurface(p);
	}

	void operator()(TTF_Font* p) const
	{
		TTF_CloseFont(p);
	}

	void operator()(Mix_Music* p) const
	{
		Mix_FreeMusic(p);
	}
};
