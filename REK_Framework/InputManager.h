#pragma once
#include <SDL2/SDL.h>
#include "InputKeyboardManager.h"
#include "InputGamepadManager.h"
#include <vector>
#include <algorithm>
#include "GamepadConfiguration.h"

namespace REKFramework
{
	class InputManager
	{
	public:
		InputManager(std::shared_ptr<GameContextManager> gameContextManager);
		~InputManager();

		void CheckInput(SDL_Event& e, bool& quitGame);

	private:
		std::unique_ptr<SDL_Event> PressedInput;
		std::unique_ptr<InputKeyboardManager> keyboardManager;
		std::unique_ptr<InputGamepadManager> gamepadManager;
		std::unique_ptr<GamepadConfiguration> gamepadCnfg;
		std::shared_ptr<GameContextManager> gameContextMngr;

		bool continuousButtonPressed;

		std::vector<Uint8> gamepadButtonsPressedState;

		bool RTTriggered;
		bool LTTriggered;

		bool canCheckKeyboardInput;

		void SetPressedButton();
		void SetReleasedButton();

		void SetAxisMotion();

		void CheckInputNotHold();

		void CheckGamepadInput() const;
		void CheckGamepadAxisMotion() const;
	};
}