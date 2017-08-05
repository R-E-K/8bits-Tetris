#pragma once
#include <SDL2/SDL.h>
#include "GameContextManager.h"

namespace REKFramework
{
	class InputGamepadManager
	{
	public:
		InputGamepadManager(std::shared_ptr<GameContextManager> gameContextManager);
		~InputGamepadManager();

		void CheckInput(Uint8 pressedButton) const;
		void CheckReleasedInput(Uint8 releasedButton) const;
		void CheckAxisMotion(Uint8 axisMotion) const;
	private:
		std::shared_ptr<GameContextManager> gameContextMngr;
	};
}

