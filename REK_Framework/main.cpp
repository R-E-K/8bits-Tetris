#pragma once
#include "Game.h"

int main(int argc, char* args[])
{
	Game* game = new Game();

	if (game->Init())
	{
		SDL_Event e;
		game->Loop(&e);
	}
	
	delete game;
	
	return 0;
}
