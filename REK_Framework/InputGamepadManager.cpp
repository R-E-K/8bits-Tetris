#pragma once
#include "InputGamepadManager.h"

namespace REKFramework
{
	InputGamepadManager::InputGamepadManager(std::shared_ptr<GameContextManager> gameContextManager)
	{
		gameContextMngr = gameContextManager;
	}

	InputGamepadManager::~InputGamepadManager()
	{

	}

	void InputGamepadManager::CheckInput(Uint8 pressedButton) const
	{
		switch (pressedButton)
		{
		case SDL_CONTROLLER_BUTTON_A:
			gameContextMngr->ExecuteAButtonAction();
			break;
		case SDL_CONTROLLER_BUTTON_B:
			gameContextMngr->ExecuteBButtonAction();
			break;
		case SDL_CONTROLLER_BUTTON_X:
			gameContextMngr->ExecuteXButtonAction();
			break;
		case SDL_CONTROLLER_BUTTON_Y:
			gameContextMngr->ExecuteYButtonAction();
			break;
		case SDL_CONTROLLER_BUTTON_LEFTSHOULDER:
			gameContextMngr->ExecuteLBButtonAction();
			break;
		case SDL_CONTROLLER_BUTTON_RIGHTSHOULDER:
			gameContextMngr->ExecuteRBButtonAction();
			break;
		case SDL_CONTROLLER_BUTTON_LEFTSTICK:
			gameContextMngr->ExecuteL3ButtonAction();
			break;
		case SDL_CONTROLLER_BUTTON_RIGHTSTICK:
			gameContextMngr->ExecuteR3ButtonAction();
			break;
		case SDL_CONTROLLER_BUTTON_START:
			gameContextMngr->ExecuteStartButtonAction();
			break;
		case SDL_CONTROLLER_BUTTON_BACK:
			gameContextMngr->ExecuteBackButtonAction();
			break;
		case SDL_CONTROLLER_BUTTON_DPAD_DOWN:
			gameContextMngr->ExecuteDPadDownButtonAction();
			break;
		case SDL_CONTROLLER_BUTTON_DPAD_UP:
			gameContextMngr->ExecuteDPadUpButtonAction();
			break;
		case SDL_CONTROLLER_BUTTON_DPAD_LEFT:
			gameContextMngr->ExecuteDPadLeftButtonAction();
			break;
		case SDL_CONTROLLER_BUTTON_DPAD_RIGHT:
			gameContextMngr->ExecuteDPadRightButtonAction();
			break;
		}
	}

	void InputGamepadManager::CheckAxisMotion(Uint8 axisMotion) const
	{
		switch (axisMotion)
		{
		case SDL_CONTROLLER_AXIS_TRIGGERLEFT:
			gameContextMngr->ExecuteLTTriggerAction();
			break;
		case SDL_CONTROLLER_AXIS_TRIGGERRIGHT:
			gameContextMngr->ExecuteRTTriggerAction();
			break;
		}
	}
}
