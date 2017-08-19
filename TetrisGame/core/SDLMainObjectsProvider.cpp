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
		if (_renderer != nullptr)
		{
			return _renderer.get();
		}
		else
		{
			// TODO : Handle Exception
		}
	}

	SDL_Window* SDLMainObjectsProvider::GetWindowRawPointer()
	{
		if (_window != nullptr)
		{
			return _window.get();
		}
		else
		{
			// TODO : Handle Exception
		}
	}
}
