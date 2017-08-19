#include "Timer.h"

// !!! Have to be here and not in Timer.h !!!
// !!! Otherwise, we have a circular dependency !!!
#include "GameContextManager.h"

namespace REKTetrisGame
{
	Timer::Timer()
	{
		_lastTime = 0;
	}

	Timer::Timer(int inputRepeatFrequency)
	{
		_inputRepeatFrequency = inputRepeatFrequency;
		_lastTime = 0;
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
			_currentTime = SDL_GetTicks();

			if (_delay < _currentTime)
			{
				if (_lastTime == 0)
				{
					_lastTime = SDL_GetTicks();
				}

				if (_currentTime - _lastTime >= _inputRepeatFrequency)
				{
					function();
					_lastTime = SDL_GetTicks();
				}
			}
		}
		else
		{
			// Keep the same difference time between current time and last execution time
			// When the game is paused
			// Unless, the timer will be executed to fast when leaving pause
			int difference = _currentTime - _lastTime;
			_currentTime = SDL_GetTicks();
			_lastTime = _currentTime - difference;
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
