#pragma once
#include <SDL2/SDL.h>
#include <memory>


namespace REKFramework
{
	class SDLMainObjectsProvider
	{
	public:
		friend class Game;

		SDLMainObjectsProvider();
		~SDLMainObjectsProvider();

		static std::shared_ptr<SDL_Renderer> GetRenderer();
		static std::shared_ptr<SDL_Window> GetWindow();

		static SDL_Renderer* GetRendererPointer();
		static SDL_Window* GetWindowPointer();

	private:
		static std::shared_ptr<SDL_Renderer> renderer;
		static std::shared_ptr<SDL_Window> window;
	};
}

