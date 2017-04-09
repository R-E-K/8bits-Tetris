#pragma once
#include "ErrorMessageManager.h"

using namespace std;

ErrorMessageManager::ErrorMessageManager()
{
}


ErrorMessageManager::~ErrorMessageManager()
{
}

void ErrorMessageManager::WriteErrorMessageToConsole(char* userMessage)
{
	cout << userMessage << SDL_GetError();
}
