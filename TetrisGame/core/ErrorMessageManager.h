#pragma once
#include <SDL2/SDL.h>
#include <iostream>
#include "SDLMainObjectsProvider.h"

namespace REKTetrisGame
{
	class ErrorMessageManager
	{
	public:
		ErrorMessageManager();
		~ErrorMessageManager();

		static void WriteErrorMessageToConsole(std::string const& userMessage);
		static void WriteErrorMessageToMessageBox(std::string const& message);
	};
}

