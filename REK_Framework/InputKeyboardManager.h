#pragma once
#include <SDL2/SDL.h>
#include "DrawPictureManager.h"
#include "GameContextManager.h"

namespace REKFramework
{
	class InputKeyboardManager
	{
	public:
		explicit InputKeyboardManager(GameContextManager* gameContextManager);
		~InputKeyboardManager();

		void CheckInputHold() const;
		void CheckInputNotHold(SDL_Scancode scan) const;
	private:
		GameContextManager* gameContextMngr;
	};
}