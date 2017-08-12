#pragma once
#include <SDL2/SDL.h>
#include <functional>
#include "../BaseTimer.h"

namespace REKFramework
{
	class Timer : public BaseTimer
	{
	public:
		Timer();
		Timer(int inputRepeatFrequency);
		~Timer();

		int GetRepeatFrequency() const;

		void Execute(std::function<void()> function) override;
		void SetRepeatFrequency(int inputRepeatFrequency);
		void SetDelay(int delay) override;

	private:
		int lastTime;
		int _inputRepeatFrequency;
	};

}
