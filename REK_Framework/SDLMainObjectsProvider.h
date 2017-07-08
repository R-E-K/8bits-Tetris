#pragma once
#include <SDL2/SDL.h>


namespace REKFramework
{
	class SDLMainObjectsProvider
	{
	public:
		friend class Game;

		SDLMainObjectsProvider();
		~SDLMainObjectsProvider();

		static SDL_Renderer* GetRenderer();
		static SDL_Window* GetWindow();

	private:
		static SDL_Renderer* renderer;
		static SDL_Window* window;
	};
}

