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

	void ErrorMessageManager::WriteErrorMessageToMessageBox(std::string const& message)
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "ERROR", message.c_str(), SDLMainObjectsProvider::GetWindowRawPointer());
	}
}
