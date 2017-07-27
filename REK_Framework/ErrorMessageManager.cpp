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

	void ErrorMessageManager::WriteErrorMessageToConsole(std::string const& userMessage)
	{
		std::cout << userMessage.c_str() << SDL_GetError();
	}
}