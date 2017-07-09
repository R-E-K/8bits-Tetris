#pragma once
#include "../REK_Framework/Game.h"
#include <memory>

int main(int argc, char* args[])
{
	std::unique_ptr<REKFramework::Game> game(new REKFramework::Game);

	game->Execute();
	
	return 0;
}
