#pragma once
#include "InputKeyboardManager.h"

namespace REKTetrisGame
{
	InputKeyboardManager::InputKeyboardManager(std::shared_ptr<GameContextManager> gameContextManager)
	{
		gameContextMngr = gameContextManager;
	}

	InputKeyboardManager::~InputKeyboardManager()
	{

	}

	void InputKeyboardManager::CheckInputHold() const
	{
		auto PressedKeys = SDL_GetKeyboardState(nullptr);

		if (PressedKeys[SDL_SCANCODE_W] || PressedKeys[SDL_SCANCODE_UP])
		{
			gameContextMngr->ExecuteDPadUpButtonAction();
		}

		if (PressedKeys[SDL_SCANCODE_A] || PressedKeys[SDL_SCANCODE_LEFT])
		{
			gameContextMngr->ExecuteDPadLeftButtonAction();
		}

		if (PressedKeys[SDL_SCANCODE_S] || PressedKeys[SDL_SCANCODE_DOWN])
		{
			gameContextMngr->ExecuteDPadDownButtonAction();
		}

		if (PressedKeys[SDL_SCANCODE_D] || PressedKeys[SDL_SCANCODE_RIGHT])
		{
			gameContextMngr->ExecuteDPadRightButtonAction();
		}

		if (PressedKeys[SDL_SCANCODE_SPACE] || PressedKeys[SDL_SCANCODE_RETURN] || PressedKeys[SDL_SCANCODE_C])
		{
			gameContextMngr->ExecuteAButtonAction();
		}

		if (PressedKeys[SDL_SCANCODE_BACKSPACE])
		{
			gameContextMngr->ExecuteBButtonAction();
		}

		if (PressedKeys[SDL_SCANCODE_X])
		{
			gameContextMngr->ExecuteXButtonAction();
		}

		if (PressedKeys[SDL_SCANCODE_2])
		{
			gameContextMngr->ExecuteYButtonAction();
		}

		if (PressedKeys[SDL_SCANCODE_ESCAPE])
		{
			gameContextMngr->ExecuteStartButtonAction();
		}

		// etc...
	}

	void InputKeyboardManager::CheckInputNotHold(SDL_Scancode scan) const
	{
		switch (scan)
		{
		case SDL_SCANCODE_W:
		case SDL_SCANCODE_UP:
			gameContextMngr->ExecuteDPadUpButtonAction();
			break;
		case SDL_SCANCODE_A:
		case SDL_SCANCODE_LEFT:
			gameContextMngr->ExecuteDPadLeftButtonAction();
			break;
		case SDL_SCANCODE_S:
		case SDL_SCANCODE_DOWN:
			gameContextMngr->ExecuteDPadDownButtonAction();
			break;
		case SDL_SCANCODE_D:
		case SDL_SCANCODE_RIGHT:
			gameContextMngr->ExecuteDPadRightButtonAction();
			break;
		case SDL_SCANCODE_SPACE:
		case SDL_SCANCODE_RETURN:
			gameContextMngr->ExecuteAButtonAction();
			break;
		case SDL_SCANCODE_BACKSPACE:
			gameContextMngr->ExecuteBButtonAction();
			break;
		case SDL_SCANCODE_ESCAPE:
			gameContextMngr->ExecuteStartButtonAction();
			break;
		}
	}

	void InputKeyboardManager::CheckReleaseInput(SDL_Scancode scan) const
	{
		switch (scan)
		{
		case SDL_SCANCODE_S:
		case SDL_SCANCODE_DOWN:
			gameContextMngr->ExecuteDPadDownButtonReleaseAction();
			break;
		}
	}
}
