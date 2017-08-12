#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <memory>
#include <ctime>
#include "core/Game.h"

namespace REKFramework
{
	void GameExecution();
	void ExitSDL();

	#ifdef __cplusplus
		extern "C"
	#endif
	int main(int argc, char *argv[])
	{
		// Init Randomness
		srand(time(nullptr));

		GameExecution();
		ExitSDL();

		return 0;
	}

	void GameExecution()
	{
		auto game = std::make_unique<Game>();
		game->Execute();
	}

	void ExitSDL()
	{
		SDL_DestroyRenderer(SDLMainObjectsProvider::GetRendererRawPointer());
		SDL_DestroyWindow(SDLMainObjectsProvider::GetWindowRawPointer());

		//Quit SDL subsystems

		TTF_Quit();
		IMG_Quit();

		SDL_Quit();
	}
}
