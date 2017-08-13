#pragma once
#include "ErrorMessageManager.h"

namespace REKTetrisGame
{
	ErrorMessageManager::ErrorMessageManager()
	{
	}


	ErrorMessageManager::~ErrorMessageManager()
	{
	}

	void ErrorMessageManager::WriteErrorMessageToConsole(std::string const& userMessage)
	{
		std::cout << userMessage.c_str() << SDL_GetError();
	}
}