#include "InputTimer.h"

namespace REKTetrisGame
{

	InputTimer::InputTimer()
	{
		InputDownLastTime = 0;
		InputDownHoldTime = 0;
	}

	InputTimer::InputTimer(int inputRepeatFrequency)
	{
		_inputRepeatFrequency = inputRepeatFrequency;
		_startHoldInputDownDelay = 0;
		InputDownLastTime = 0;
		InputDownHoldTime = 0;
	}

	InputTimer::InputTimer(int inputRepeatFrequency, int startHoldInputDownDelay)
	{
		_inputRepeatFrequency = inputRepeatFrequency;
		_startHoldInputDownDelay = startHoldInputDownDelay;
		InputDownLastTime = 0;
		InputDownHoldTime = 0;
	}

	InputTimer::~InputTimer()
	{
	}

	void InputTimer::Execute(std::function<void()> function)
	{
		currentTime = SDL_GetTicks();

		if (_delay < currentTime)
		{
			// Check at 20 ms. If less, gamepad inputs aren't recognized continously
			// Maybe a SDL bug, because if an another key is down, gamepad input is recognized continously
			IsHoldInputDown = (currentTime - InputDownLastTime <= HOLD_THRESHOLD_MS);

			if (IsHoldInputDown)
			{
				if (!IsStartingHoldInputDown)
				{
					if (currentTime - InputDownHoldTime >= _inputRepeatFrequency)
					{
						function();
						InputDownHoldTime = currentTime;
					}
				}
				else
				{
					IsStartingHoldInputDown = false;
					InputDownHoldTime = currentTime + _startHoldInputDownDelay;
				}
			}
			else if (!IsHoldInputDown)
			{
				if (InputDownLastTime == 0)
				{
					InputDownLastTime = SDL_GetTicks();
				}
				// If not safety threshold, it will be repeated continously
				if (currentTime - InputDownLastTime >= SAFETY_THRESHOLD_MS)
				{
					function();
					IsStartingHoldInputDown = true;
				}
				InputDownLastTime = currentTime;
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
