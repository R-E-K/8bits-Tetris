#pragma once
#include "../REK_Framework/Game.h"

int main(int argc, char* args[])
{
	REKFramework::Game* game = new REKFramework::Game();

	game->Execute();
	
	delete game;
	
	return 0;
}
