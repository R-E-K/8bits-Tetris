#pragma once
#include <SDL2/SDL.h>
#include "GameContextManager.h"

namespace REKFramework
{
	class InputGamepadManager
	{
	public:
		explicit InputGamepadManager(GameContextManager* gameContextManager);
		~InputGamepadManager();

		void CheckInput(Uint8 pressedButton) const;
		void CheckAxisMotion(Uint8 axisMotion) const;
	private:
		GameContextManager* gameContextMngr;
	};
}

