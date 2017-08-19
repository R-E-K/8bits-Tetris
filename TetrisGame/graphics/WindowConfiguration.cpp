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
		auto fullscreenFlag = SDL_WINDOW_FULLSCREEN;
		bool isFullscreen = SDL_GetWindowFlags(SDLMainObjectsProvider::GetWindowRawPointer()) & fullscreenFlag;
		return isFullscreen;
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
