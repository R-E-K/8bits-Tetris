#pragma once
#include <SDL2/SDL_video.h>
#include "../core/SDLMainObjectsProvider.h"

namespace REKTetrisGame
{
	class WindowConfiguration
	{
	public:
		WindowConfiguration();
		~WindowConfiguration();

		static bool IsFullScreen();
		static void ToggleFullScreen();
	};
}

