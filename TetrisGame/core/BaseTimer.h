#pragma once
#include <functional>

namespace REKTetrisGame
{
	class BaseTimer
	{
	public:
		BaseTimer();
		virtual ~BaseTimer();

		// "= 0" make the method Pure virtual. If a class have, at least, one pure virtual method : It will be abstract
		virtual void Execute(std::function<void()> function) = 0;
		virtual void SetDelay(int delay);

	protected:
		int _currentTime;
		int _delay;
	};
}

