#pragma once
#include "../REK_Framework/Game.h"

int main(int argc, char* args[])
{
	REKFramework::Game* game = new REKFramework::Game();

	if (game->Init())
	{
		SDL_Event e;
		game->Loop(&e);
	}
	
	delete game;
	
	return 0;
}
