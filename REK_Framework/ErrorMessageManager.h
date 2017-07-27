#pragma once
#include <SDL2/SDL.h>
#include <iostream>

namespace REKFramework
{
	class ErrorMessageManager
	{
	public:
		ErrorMessageManager();
		~ErrorMessageManager();

		static void WriteErrorMessageToConsole(std::string const& userMessage);
	};
}

