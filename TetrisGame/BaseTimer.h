#pragma once
#include <functional>

namespace REKFramework
{
	class BaseTimer
	{
	public:
		BaseTimer();
		virtual ~BaseTimer();

		virtual void Execute(std::function<void()> function);
		virtual void SetDelay(int delay);

	protected:
		int currentTime;
		int _delay;
	};
}

