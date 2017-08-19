#pragma once
#include "InputGamepadManager.h"

namespace REKTetrisGame
{
	InputGamepadManager::InputGamepadManager(std::shared_ptr<GameContextManager> gameContextManager)
	{
		_gameContextManager = gameContextManager;
	}

	InputGamepadManager::~InputGamepadManager()
	{

	}

	void InputGamepadManager::CheckInput(Uint8 pressedButton) const
	{
		switch (pressedButton)
		{
		case SDL_CONTROLLER_BUTTON_A:
			_gameContextManager->ExecuteAButtonAction();
			break;
		case SDL_CONTROLLER_BUTTON_B:
			_gameContextManager->ExecuteBButtonAction();
			break;
		case SDL_CONTROLLER_BUTTON_X:
			_gameContextManager->ExecuteXButtonAction();
			break;
		case SDL_CONTROLLER_BUTTON_Y:
			_gameContextManager->ExecuteYButtonAction();
			break;
		case SDL_CONTROLLER_BUTTON_LEFTSHOULDER:
			_gameContextManager->ExecuteLBButtonAction();
			break;
		case SDL_CONTROLLER_BUTTON_RIGHTSHOULDER:
			_gameContextManager->ExecuteRBButtonAction();
			break;
		case SDL_CONTROLLER_BUTTON_LEFTSTICK:
			_gameContextManager->ExecuteL3ButtonAction();
			break;
		case SDL_CONTROLLER_BUTTON_RIGHTSTICK:
			_gameContextManager->ExecuteR3ButtonAction();
			break;
		case SDL_CONTROLLER_BUTTON_START:
			_gameContextManager->ExecuteStartButtonAction();
			break;
		case SDL_CONTROLLER_BUTTON_BACK:
			_gameContextManager->ExecuteBackButtonAction();
			break;
		case SDL_CONTROLLER_BUTTON_DPAD_DOWN:
			_gameContextManager->ExecuteDPadDownButtonAction();
			break;
		case SDL_CONTROLLER_BUTTON_DPAD_UP:
			_gameContextManager->ExecuteDPadUpButtonAction();
			break;
		case SDL_CONTROLLER_BUTTON_DPAD_LEFT:
			_gameContextManager->ExecuteDPadLeftButtonAction();
			break;
		case SDL_CONTROLLER_BUTTON_DPAD_RIGHT:
			_gameContextManager->ExecuteDPadRightButtonAction();
			break;
		}
	}

	void InputGamepadManager::CheckReleasedInput(Uint8 releasedButton) const
	{
		switch (releasedButton)
		{
		case SDL_CONTROLLER_BUTTON_DPAD_DOWN:
			_gameContextManager->ExecuteDPadDownButtonReleaseAction();
			break;
		}
	}

	void InputGamepadManager::CheckAxisMotion(Uint8 axisMotion) const
	{
		switch (axisMotion)
		{
		case SDL_CONTROLLER_AXIS_TRIGGERLEFT:
			_gameContextManager->ExecuteLTTriggerAction();
			break;
		case SDL_CONTROLLER_AXIS_TRIGGERRIGHT:
			_gameContextManager->ExecuteRTTriggerAction();
			break;
		}
	}
}
