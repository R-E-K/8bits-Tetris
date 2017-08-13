#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

namespace REKTetrisGame
{
	// Functor wrapping SDL structs destruction
	struct SdlDeleter
	{
		void operator()(SDL_Window* p) const;
		void operator()(SDL_Renderer* p) const;
		void operator()(SDL_GameController* p) const;
		void operator()(SDL_Texture* p) const;
		void operator()(SDL_Surface* p) const;
		void operator()(TTF_Font* p) const;
		void operator()(Mix_Music* p) const;
		void operator()(Mix_Chunk* p) const;
	};
}