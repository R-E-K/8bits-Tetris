#include "WindowConfiguration.h"


namespace REKTetrisGame
{
	WindowConfiguration::WindowConfiguration()
	{
	}


	WindowConfiguration::~WindowConfiguration()
	{
	}

	bool WindowConfiguration::IsFullScreen()
	{
		auto FullscreenFlag = SDL_WINDOW_FULLSCREEN;
		bool IsFullscreen = SDL_GetWindowFlags(SDLMainObjectsProvider::GetWindowRawPointer()) & FullscreenFlag;
		return IsFullscreen;
	}

	void WindowConfiguration::ToggleFullScreen()
	{
		if (IsFullScreen())
		{
			SDL_SetWindowFullscreen(SDLMainObjectsProvider::GetWindowRawPointer(), SDL_WINDOW_SHOWN);
		}
		else
		{
			SDL_SetWindowFullscreen(SDLMainObjectsProvider::GetWindowRawPointer(), SDL_WINDOW_FULLSCREEN_DESKTOP);
		}
	}
}
