#pragma once
#include "InputManager.h"


namespace REKFramework
{
	InputManager::InputManager(std::shared_ptr<GameContextManager> gameContextManager)
	{
		PressedInput = nullptr;
		keyboardManager = std::make_unique<InputKeyboardManager>(gameContextManager);
		gamepadManager = std::make_unique<InputGamepadManager>(gameContextManager);
		gamepadCnfg = std::make_unique<GamepadConfiguration>();

		gameContextMngr = gameContextManager;

		LTTriggered = false;
		RTTriggered = false;

		canCheckKeyboardInput = false;

		gamepadButtonsPressedState.clear();
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
			PressedInput = std::make_unique<SDL_Event>(e);

			switch (PressedInput->type)
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
				gamepadCnfg->PlugGamepad();
				break;
			case SDL_CONTROLLERDEVICEREMOVED:
				gamepadCnfg->UnplugGamepad();
				break;
			}

			if (LTTriggered || RTTriggered) CheckGamepadAxisMotion();

			if (GameContextManager::CurrentGameContext == GameContextEnum::INGAME && !canCheckKeyboardInput)
				keyboardManager->CheckInputHold();

			CheckGamepadInput();

		}
		if (LTTriggered || RTTriggered) CheckGamepadAxisMotion();

		if (GameContextManager::CurrentGameContext == GameContextEnum::INGAME && !canCheckKeyboardInput)
			keyboardManager->CheckInputHold();

		CheckGamepadInput();
	}

	void InputManager::SetPressedButton()
	{
		if (PressedInput != nullptr &&
			&PressedInput->jbutton != nullptr &&
			&PressedInput->jbutton.button != nullptr)
		{
			if (GameContextManager::CurrentGameContext == GameContextEnum::INGAME
				&& PressedInput->jbutton.button != SDL_CONTROLLER_BUTTON_START)
			{
				gamepadButtonsPressedState.push_back(PressedInput->jbutton.button);
			}
			else
			{
				gamepadManager->CheckInput(PressedInput->jbutton.button);
			}
		}
	}

	void InputManager::SetReleasedButton()
	{
		if (PressedInput != nullptr &&
			&PressedInput->jbutton != nullptr &&
			&PressedInput->jbutton.button != nullptr)
		{
			gamepadManager->CheckReleasedInput(PressedInput->jbutton.button);

			// We check that element exists in vector before remove it
			if (find(gamepadButtonsPressedState.begin(), gamepadButtonsPressedState.end(), PressedInput->jbutton.button)
				!= gamepadButtonsPressedState.end())
			{
				gamepadButtonsPressedState.erase(remove(gamepadButtonsPressedState.begin(),
					gamepadButtonsPressedState.end(), PressedInput->jbutton.button));
			}

		}
	}

	void InputManager::SetAxisMotion()
	{
		if (PressedInput != nullptr &&
			&PressedInput->jaxis != nullptr &&
			&PressedInput->jaxis.axis != nullptr &&
			&PressedInput->jaxis.value != nullptr)
		{
			if (GameContextManager::CurrentGameContext == GameContextEnum::INGAME)
			{
				if (PressedInput->jaxis.axis == SDL_CONTROLLER_AXIS_TRIGGERLEFT)
				{
					LTTriggered = (PressedInput->jaxis.value > 20000);
				}

				if (PressedInput->jaxis.axis == SDL_CONTROLLER_AXIS_TRIGGERRIGHT)
				{
					RTTriggered = (PressedInput->jaxis.value > 20000);
				}
			}
			else
			{
				if (
					(!LTTriggered && PressedInput->jaxis.axis == SDL_CONTROLLER_AXIS_TRIGGERLEFT
						&& PressedInput->jaxis.axis > 20000)
					||
					(!RTTriggered && PressedInput->jaxis.axis == SDL_CONTROLLER_AXIS_TRIGGERRIGHT
						&& PressedInput->jaxis.axis > 20000)
					)
				{
					gamepadManager->CheckAxisMotion(PressedInput->jaxis.axis);
				}
			}

		}
	}

	void InputManager::CheckInputNotHold()
	{
		if (PressedInput != nullptr &&
			&PressedInput->key != nullptr &&
			&PressedInput->key.keysym != nullptr &&
			&PressedInput->key.keysym.scancode != nullptr)
		{
			if (
				(GameContextManager::CurrentGameContext == GameContextEnum::INGAME &&
					PressedInput->key.keysym.scancode == SDL_SCANCODE_ESCAPE)
				||
				GameContextManager::CurrentGameContext == GameContextEnum::MENU
				||
				GameContextManager::CurrentGameContext == GameContextEnum::GAMEOVER
				)
			{
				keyboardManager->CheckInputNotHold(PressedInput->key.keysym.scancode);
				canCheckKeyboardInput = true;
			}
		}
	}

	void InputManager::CheckReleaseInput()
	{
		if (PressedInput != nullptr &&
			&PressedInput->key != nullptr &&
			&PressedInput->key.keysym != nullptr &&
			&PressedInput->key.keysym.scancode != nullptr)
		{

			keyboardManager->CheckReleaseInput(PressedInput->key.keysym.scancode);
			canCheckKeyboardInput = false;
		}
	}

	void InputManager::CheckGamepadInput() const
	{
		if (!gamepadButtonsPressedState.empty())
		{
			for (auto pressedButton : gamepadButtonsPressedState)
			{
				gamepadManager->CheckInput(pressedButton);
			}
		}
	}

	void InputManager::CheckGamepadAxisMotion() const
	{
		if (LTTriggered)
		{
			gamepadManager->CheckAxisMotion(SDL_CONTROLLER_AXIS_TRIGGERLEFT);
		}

		if (RTTriggered)
		{
			gamepadManager->CheckAxisMotion(SDL_CONTROLLER_AXIS_TRIGGERRIGHT);
		}
	}
}