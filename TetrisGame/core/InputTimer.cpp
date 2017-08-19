#include "InputTimer.h"

namespace REKTetrisGame
{

	InputTimer::InputTimer()
	{
		_inputDownLastTime = 0;
		_inputDownHoldTime = 0;
	}

	InputTimer::InputTimer(int inputRepeatFrequency)
	{
		_inputRepeatFrequency = inputRepeatFrequency;
		_startHoldInputDownDelay = 0;
		_inputDownLastTime = 0;
		_inputDownHoldTime = 0;
	}

	InputTimer::InputTimer(int inputRepeatFrequency, int startHoldInputDownDelay)
	{
		_inputRepeatFrequency = inputRepeatFrequency;
		_startHoldInputDownDelay = startHoldInputDownDelay;
		_inputDownLastTime = 0;
		_inputDownHoldTime = 0;
	}

	InputTimer::~InputTimer()
	{
	}

	void InputTimer::Execute(std::function<void()> function)
	{
		_currentTime = SDL_GetTicks();

		if (_delay < _currentTime)
		{
			// Check at 20 ms. If less, gamepad inputs aren't recognized continously
			// Maybe a SDL bug, because if an another key is down, gamepad input is recognized continously
			_isHoldInputDown = (_currentTime - _inputDownLastTime <= HOLD_THRESHOLD_MS);

			if (_isHoldInputDown)
			{
				if (!_isStartingHoldInputDown)
				{
					if (_currentTime - _inputDownHoldTime >= _inputRepeatFrequency)
					{
						function();
						_inputDownHoldTime = _currentTime;
					}
				}
				else
				{
					_isStartingHoldInputDown = false;
					_inputDownHoldTime = _currentTime + _startHoldInputDownDelay;
				}
			}
			else if (!_isHoldInputDown)
			{
				if (_inputDownLastTime == 0)
				{
					_inputDownLastTime = SDL_GetTicks();
				}
				// If not safety threshold, it will be repeated continously
				if (_currentTime - _inputDownLastTime >= SAFETY_THRESHOLD_MS)
				{
					function();
					_isStartingHoldInputDown = true;
				}
				_inputDownLastTime = _currentTime;
			}
		}
	}

	void InputTimer::SetInputRepeatFrequency(int inputRepeatFrequency)
	{
		_inputRepeatFrequency = inputRepeatFrequency;
	}

	void InputTimer::SetStartHoldInputDownDelay(int startHoldInputDownDelay)
	{
		_startHoldInputDownDelay = startHoldInputDownDelay;
	}

	void InputTimer::SetDelay(int delay)
	{
		BaseTimer::SetDelay(delay);
	}
}
