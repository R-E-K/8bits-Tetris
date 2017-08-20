#pragma once
#include "SDLMainObjectsProvider.h"

namespace REKTetrisGame
{
	std::shared_ptr<SDL_Renderer> SDLMainObjectsProvider::_renderer;
	std::shared_ptr<SDL_Window> SDLMainObjectsProvider::_window;


	SDLMainObjectsProvider::SDLMainObjectsProvider()
	{
	}


	SDLMainObjectsProvider::~SDLMainObjectsProvider()
	{
	}

	std::shared_ptr<SDL_Renderer> SDLMainObjectsProvider::GetRenderer()
	{
		return _renderer;
	}

	std::shared_ptr<SDL_Window> SDLMainObjectsProvider::GetWindow()
	{
		return _window;
	}

	SDL_Renderer* SDLMainObjectsProvider::GetRendererRawPointer()
	{
		return _renderer.get();
	}

	SDL_Window* SDLMainObjectsProvider::GetWindowRawPointer()
	{
		return _window.get();
	}
}
