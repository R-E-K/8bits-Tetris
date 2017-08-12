#pragma once
#include <SDL2/SDL.h>
#include <memory>
#include "../core/GameContextManager.h"

namespace REKFramework
{
	class InputKeyboardManager
	{
	public:
		InputKeyboardManager(std::shared_ptr<GameContextManager> gameContextManager);
		~InputKeyboardManager();

		void CheckInputHold() const;
		void CheckInputNotHold(SDL_Scancode scan) const;
		void CheckReleaseInput(SDL_Scancode scan) const;
	private:
		std::shared_ptr<GameContextManager> gameContextMngr;
	};
}
