#include "Timer.h"

// !!! Have to be here and not in Timer.h !!!
// !!! Otherwise, we have a circular dependency !!!
#include "GameContextManager.h"

namespace REKTetrisGame
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

	int Timer::GetRepeatFrequency() const
	{
		return _inputRepeatFrequency;
	}

	void Timer::Execute(std::function<void()> function)
	{
		if (!GameContextManager::IsGamePaused())
		{
			currentTime = SDL_GetTicks();

			if (_delay < currentTime)
			{
				if (lastTime == 0)
				{
					lastTime = SDL_GetTicks();
				}

				if (currentTime - lastTime >= _inputRepeatFrequency)
				{
					function();
					lastTime = SDL_GetTicks();
				}
			}
		}
		else
		{
			// Keep the same difference time between current time and last execution time
			// When the game is paused
			// Unless, the timer will be executed to fast when leaving pause
			int difference = currentTime - lastTime;
			currentTime = SDL_GetTicks();
			lastTime = currentTime - difference;
		}
			
	}

	void Timer::SetRepeatFrequency(int inputRepeatFrequency)
	{
		_inputRepeatFrequency = inputRepeatFrequency;
	}

	void Timer::SetDelay(int delay)
	{
		BaseTimer::SetDelay(delay);
	}
}
