#pragma once
#include <SDL2/SDL.h>
#include <functional>
#include "../BaseTimer.h"

namespace REKFramework
{
	class InputTimer : public BaseTimer
	{
	public:
		InputTimer();
		InputTimer(int inputRepeatFrequency);
		InputTimer(int inputRepeatFrequency, int startHoldInputDownDelay);
		~InputTimer();

		void Execute(std::function<void()> function) override;
		void SetInputRepeatFrequency(int inputRepeatFrequency);
		void SetStartHoldInputDownDelay(int startHoldInputDownDelay);
		void SetDelay(int delay) override;

	private:

		const int SAFETY_THRESHOLD_MS = 50;
		const int HOLD_THRESHOLD_MS = 20;

		int InputDownLastTime;
		int InputDownHoldTime;
		bool IsHoldInputDown;
		bool IsStartingHoldInputDown;

		int _startHoldInputDownDelay;
		int _inputRepeatFrequency;
	};
}

