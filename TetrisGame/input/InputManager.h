#pragma once
#include <SDL2/SDL.h>
#include "InputKeyboardManager.h"
#include "InputGamepadManager.h"
#include <vector>
#include <algorithm>
#include "GamepadConfiguration.h"

namespace REKTetrisGame
{
	class InputManager
	{
	public:
		InputManager(std::shared_ptr<GameContextManager> gameContextManager);
		~InputManager();

		void CheckInput(SDL_Event& e, bool& quitGame);
		std::shared_ptr<GamepadConfiguration> GetGamepadConfiguration() const;

	private:
		std::unique_ptr<SDL_Event> _pressedInput;
		std::unique_ptr<InputKeyboardManager> _keyboardManager;
		std::unique_ptr<InputGamepadManager> _gamepadManager;
		std::shared_ptr<GamepadConfiguration> _gamepadConfiguration;
		std::shared_ptr<GameContextManager> _gameContextManager;

		std::vector<Uint8> _gamepadButtonsPressedState;

		bool _rtTriggered;
		bool _ltTriggered;

		bool _canCheckKeyboardInput;

		void SetPressedButton();
		void SetReleasedButton();

		void SetAxisMotion();

		void CheckInputNotHold();
		void CheckReleaseInput();

		void CheckGamepadInput() const;
		void CheckGamepadAxisMotion() const;
	};
}