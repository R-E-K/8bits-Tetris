#pragma once
#include "ErrorMessageManager.h"

namespace REKFramework
{
	ErrorMessageManager::ErrorMessageManager()
	{
	}


	ErrorMessageManager::~ErrorMessageManager()
	{
	}

	void ErrorMessageManager::WriteErrorMessageToConsole(char* userMessage)
	{
		std::cout << userMessage << SDL_GetError();
	}
}