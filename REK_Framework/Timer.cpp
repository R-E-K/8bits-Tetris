#include "Timer.h"

// !!! Have to be here and not in Timer.h !!!
// !!! Otherwise, we have a circular dependency !!!
#include "GameContextManager.h"

namespace REKFramework
{
	Timer::Timer()
	{
		lastTime = 0;
	}

	Timer::Timer(int inputRepeatFrequency)
	{
		_inputRepeatFrequency = inputRepeatFrequency;
		lastTime = 0;
	}

	Timer::~Timer()
	{
	}

	void Timer::Execute(std::function<void()> function)
	{
		if (!GameContextManager::IsGamePaused())
		{
			currentTime = SDL_GetTicks();

			if (currentTime - lastTime >= _inputRepeatFrequency)
			{
				function();
				lastTime = SDL_GetTicks();
			}
		}
			
	}

	void Timer::SetRepeatFrequency(int inputRepeatFrequency)
	{
		_inputRepeatFrequency = inputRepeatFrequency;
	}
}
