#pragma once
#include <SDL2/SDL.h>
#include <memory>


namespace REKTetrisGame
{
	class SDLMainObjectsProvider
	{
	public:
		friend class Game;

		SDLMainObjectsProvider();
		~SDLMainObjectsProvider();

		static std::shared_ptr<SDL_Renderer> GetRenderer();
		static std::shared_ptr<SDL_Window> GetWindow();

		static SDL_Renderer* GetRendererRawPointer();
		static SDL_Window* GetWindowRawPointer();

	private:
		static std::shared_ptr<SDL_Renderer> _renderer;
		static std::shared_ptr<SDL_Window> _window;
	};
}

