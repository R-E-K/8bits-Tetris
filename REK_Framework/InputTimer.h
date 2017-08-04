#pragma once
#include <SDL2/SDL.h>
#include <functional>

namespace REKFramework
{
	class InputTimer
	{
	public:
		InputTimer();
		InputTimer(int inputRepeatFrequency);
		InputTimer(int inputRepeatFrequency, int startHoldInputDownDelay);
		~InputTimer();

		void Execute(std::function<void()> function);
		void SetInputRepeatFrequency(int inputRepeatFrequency);
		void SetStartHoldInputDownDelay(int startHoldInputDownDelay);

	private:

		const int SAFETY_THRESHOLD_MS = 50;
		const int HOLD_THRESHOLD_MS = 20;

		int currentTime;
		int InputDownLastTime;
		int InputDownHoldTime;
		bool IsHoldInputDown;
		bool IsStartingHoldInputDown;

		int _startHoldInputDownDelay;
		int _inputRepeatFrequency;
	};
}

