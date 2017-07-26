#pragma once
#include "../REK_Framework/Game.h"
#include "../REK_Framework/SDLDeletersFunctor.h"
#include <memory>

void GameExecution();
void ExitSDL();

int main(int argc, char* args[])
{
	GameExecution();
	ExitSDL();
	
	return 0;
}

void GameExecution()
{
	auto game = std::make_unique<REKFramework::Game>();
	game->Execute();
}

void ExitSDL()
{
	// TODO : Avoid static properties in order to handle properly the destruction
	SDL_DestroyRenderer(REKFramework::SDLMainObjectsProvider::GetRendererPointer());
	SDL_DestroyWindow(REKFramework::SDLMainObjectsProvider::GetWindowPointer());

	//Quit SDL subsystems

	TTF_Quit();
	IMG_Quit();

	SDL_Quit();
}