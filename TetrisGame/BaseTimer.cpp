#include "BaseTimer.h"
#include <SDL2/SDL.h>

namespace REKFramework
{

	BaseTimer::BaseTimer()
	{
		_delay = 0;
	}


	BaseTimer::~BaseTimer()
	{
	}

	void BaseTimer::Execute(std::function<void()> function)
	{
	}

	void BaseTimer::SetDelay(int delay)
	{
		_delay = SDL_GetTicks() + delay;
	}
}
