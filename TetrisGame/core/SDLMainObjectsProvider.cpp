#pragma once
#include "SDLMainObjectsProvider.h"

namespace REKFramework
{
	std::shared_ptr<SDL_Renderer> SDLMainObjectsProvider::renderer;
	std::shared_ptr<SDL_Window> SDLMainObjectsProvider::window;


	SDLMainObjectsProvider::SDLMainObjectsProvider()
	{
	}


	SDLMainObjectsProvider::~SDLMainObjectsProvider()
	{
	}

	std::shared_ptr<SDL_Renderer> SDLMainObjectsProvider::GetRenderer()
	{
		return renderer;
	}

	std::shared_ptr<SDL_Window> SDLMainObjectsProvider::GetWindow()
	{
		return window;
	}

	SDL_Renderer* SDLMainObjectsProvider::GetRendererRawPointer()
	{
		if (renderer != nullptr)
		{
			return renderer.get();
		}
		else
		{
			// TODO : Handle Exception
		}
	}

	SDL_Window* SDLMainObjectsProvider::GetWindowRawPointer()
	{
		if (window != nullptr)
		{
			return window.get();
		}
		else
		{
			// TODO : Handle Exception
		}
	}
}
