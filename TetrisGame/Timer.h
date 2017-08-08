#pragma once
#include <SDL2/SDL.h>
#include <functional>

namespace REKFramework
{
	class Timer
	{
	public:
		Timer();
		Timer(int inputRepeatFrequency);
		~Timer();

		int GetRepeatFrequency() const;

		void Execute(std::function<void()> function);
		void SetRepeatFrequency(int inputRepeatFrequency);
		void SetDelay(int delay);

	private:
		int currentTime;
		int lastTime;
		int _inputRepeatFrequency;
		int _delay;
	};

}