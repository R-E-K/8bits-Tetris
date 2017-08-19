#pragma once
#include "InputManager.h"


namespace REKTetrisGame
{
	InputManager::InputManager(std::shared_ptr<GameContextManager> gameContextManager)
	{
		_pressedInput = nullptr;
		_keyboardManager = std::make_unique<InputKeyboardManager>(gameContextManager);
		_gamepadManager = std::make_unique<InputGamepadManager>(gameContextManager);
		_gamepadConfiguration = std::make_shared<GamepadConfiguration>();

		_gameContextManager = gameContextManager;

		_ltTriggered = false;
		_rtTriggered = false;

		_canCheckKeyboardInput = false;

		_gamepadButtonsPressedState.clear();
	}

	InputManager::~InputManager()
	{

	}

	void InputManager::CheckInput(SDL_Event& e, bool& quitGame)
	{
		// Smart pointers don't work well with SDL_PollEvent()
		// Even if i do mySmartPointer.get(), PressedInput become undefined
		while (SDL_PollEvent(&e) > 0)
		{
			_pressedInput = std::make_unique<SDL_Event>(e);

			switch (_pressedInput->type)
			{
			case SDL_QUIT:
				quitGame = true;
				break;
			case SDL_KEYDOWN:
				CheckInputNotHold();
				break;
			case SDL_KEYUP:
				CheckReleaseInput();
				break;
			case SDL_CONTROLLERBUTTONDOWN:
				SetPressedButton();
				break;
			case SDL_CONTROLLERBUTTONUP:
				SetReleasedButton();
				break;
			case SDL_CONTROLLERAXISMOTION:
				SetAxisMotion();
				break;
			case SDL_CONTROLLERDEVICEADDED:
				_gamepadConfiguration->PlugGamepad();
				break;
			case SDL_CONTROLLERDEVICEREMOVED:
				_gamepadConfiguration->UnplugGamepad();
				break;
			}

			if (_ltTriggered || _rtTriggered) CheckGamepadAxisMotion();

			if (GameContextManager::CurrentGameContext == GameContextEnum::INGAME && !_canCheckKeyboardInput)
				_keyboardManager->CheckInputHold();

			CheckGamepadInput();

		}
		if (_ltTriggered || _rtTriggered) CheckGamepadAxisMotion();

		if (GameContextManager::CurrentGameContext == GameContextEnum::INGAME && !_canCheckKeyboardInput)
			_keyboardManager->CheckInputHold();

		CheckGamepadInput();
	}

	std::shared_ptr<GamepadConfiguration> InputManager::GetGamepadConfiguration() const
	{
		return _gamepadConfiguration;
	}

	void InputManager::SetPressedButton()
	{
		if (_pressedInput != nullptr &&
			&_pressedInput->jbutton != nullptr &&
			&_pressedInput->jbutton.button != nullptr)
		{
			if (GameContextManager::CurrentGameContext == GameContextEnum::INGAME
				&& _pressedInput->jbutton.button != SDL_CONTROLLER_BUTTON_START)
			{
				_gamepadButtonsPressedState.push_back(_pressedInput->jbutton.button);
			}
			else
			{
				_gamepadManager->CheckInput(_pressedInput->jbutton.button);
			}
		}
	}

	void InputManager::SetReleasedButton()
	{
		if (_pressedInput != nullptr &&
			&_pressedInput->jbutton != nullptr &&
			&_pressedInput->jbutton.button != nullptr)
		{
			_gamepadManager->CheckReleasedInput(_pressedInput->jbutton.button);

			// We check that element exists in vector before remove it
			if (find(_gamepadButtonsPressedState.begin(), _gamepadButtonsPressedState.end(), _pressedInput->jbutton.button)
				!= _gamepadButtonsPressedState.end())
			{
				_gamepadButtonsPressedState.erase(remove(_gamepadButtonsPressedState.begin(),
					_gamepadButtonsPressedState.end(), _pressedInput->jbutton.button));
			}

		}
	}

	void InputManager::SetAxisMotion()
	{
		if (_pressedInput != nullptr &&
			&_pressedInput->jaxis != nullptr &&
			&_pressedInput->jaxis.axis != nullptr &&
			&_pressedInput->jaxis.value != nullptr)
		{
			if (GameContextManager::CurrentGameContext == GameContextEnum::INGAME)
			{
				if (_pressedInput->jaxis.axis == SDL_CONTROLLER_AXIS_TRIGGERLEFT)
				{
					_ltTriggered = (_pressedInput->jaxis.value > 20000);
				}

				if (_pressedInput->jaxis.axis == SDL_CONTROLLER_AXIS_TRIGGERRIGHT)
				{
					_rtTriggered = (_pressedInput->jaxis.value > 20000);
				}
			}
			else
			{
				if (
					(!_ltTriggered && _pressedInput->jaxis.axis == SDL_CONTROLLER_AXIS_TRIGGERLEFT
						&& _pressedInput->jaxis.axis > 20000)
					||
					(!_rtTriggered && _pressedInput->jaxis.axis == SDL_CONTROLLER_AXIS_TRIGGERRIGHT
						&& _pressedInput->jaxis.axis > 20000)
					)
				{
					_gamepadManager->CheckAxisMotion(_pressedInput->jaxis.axis);
				}
			}

		}
	}

	void InputManager::CheckInputNotHold()
	{
		if (_pressedInput != nullptr &&
			&_pressedInput->key != nullptr &&
			&_pressedInput->key.keysym != nullptr &&
			&_pressedInput->key.keysym.scancode != nullptr)
		{
			if (
				(GameContextManager::CurrentGameContext == GameContextEnum::INGAME &&
					_pressedInput->key.keysym.scancode == SDL_SCANCODE_ESCAPE)
				||
				GameContextManager::CurrentGameContext == GameContextEnum::MENU
				||
				GameContextManager::CurrentGameContext == GameContextEnum::GAMEOVER
				||
				GameContextManager::CurrentGameContext == GameContextEnum::STARTED
				)
			{
				_keyboardManager->CheckInputNotHold(_pressedInput->key.keysym.scancode);
				_canCheckKeyboardInput = true;
			}
		}
	}

	void InputManager::CheckReleaseInput()
	{
		if (_pressedInput != nullptr &&
			&_pressedInput->key != nullptr &&
			&_pressedInput->key.keysym != nullptr &&
			&_pressedInput->key.keysym.scancode != nullptr)
		{

			_keyboardManager->CheckReleaseInput(_pressedInput->key.keysym.scancode);
			_canCheckKeyboardInput = false;
		}
	}

	void InputManager::CheckGamepadInput() const
	{
		if (!_gamepadButtonsPressedState.empty())
		{
			for (auto pressedButton : _gamepadButtonsPressedState)
			{
				_gamepadManager->CheckInput(pressedButton);
			}
		}
	}

	void InputManager::CheckGamepadAxisMotion() const
	{
		if (_ltTriggered)
		{
			_gamepadManager->CheckAxisMotion(SDL_CONTROLLER_AXIS_TRIGGERLEFT);
		}

		if (_rtTriggered)
		{
			_gamepadManager->CheckAxisMotion(SDL_CONTROLLER_AXIS_TRIGGERRIGHT);
		}
	}
}