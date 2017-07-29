#pragma once
#include "SDLDeletersFunctor.h"

namespace REKFramework
{
	void SdlDeleter::operator()(SDL_Window* p) const
	{
		SDL_DestroyWindow(p);
	}

	void SdlDeleter::operator()(SDL_Renderer* p) const
	{
		SDL_DestroyRenderer(p);
	}

	void SdlDeleter::operator()(SDL_Texture* p) const
	{
		SDL_DestroyTexture(p);
	}

	void SdlDeleter::operator()(SDL_Surface* p) const
	{
		SDL_FreeSurface(p);
	}

	void SdlDeleter::operator()(TTF_Font* p) const
	{
		TTF_CloseFont(p);
	}

	void SdlDeleter::operator()(Mix_Music* p) const
	{
		Mix_FreeMusic(p);
	}

	void SdlDeleter::operator()(Mix_Chunk* p) const
	{
		Mix_FreeChunk(p);
	}
}
