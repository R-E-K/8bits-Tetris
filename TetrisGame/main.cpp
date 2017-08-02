#pragma once
#include "../REK_Framework/Game.h"
#include "../REK_Framework/SDLDeletersFunctor.h"
#include <memory>
#include <ctime>

void GameExecution();
void ExitSDL();

int main(int argc, char* args[])
{
	// Init Randomness
	srand(time(nullptr));

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
	SDL_DestroyRenderer(REKFramework::SDLMainObjectsProvider::GetRendererRawPointer());
	SDL_DestroyWindow(REKFramework::SDLMainObjectsProvider::GetWindowRawPointer());

	//Quit SDL subsystems

	TTF_Quit();
	IMG_Quit();

	SDL_Quit();
}