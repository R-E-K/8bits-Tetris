#pragma once
#include "InputKeyboardManager.h"

namespace REKTetrisGame
{
	InputKeyboardManager::InputKeyboardManager(std::shared_ptr<GameContextManager> gameContextManager)
	{
		_gameContextManager = gameContextManager;
	}

	InputKeyboardManager::~InputKeyboardManager()
	{

	}

	void InputKeyboardManager::CheckInputHold() const
	{
		auto PressedKeys = SDL_GetKeyboardState(nullptr);

		if (PressedKeys[SDL_SCANCODE_W] || PressedKeys[SDL_SCANCODE_UP])
		{
			_gameContextManager->ExecuteDPadUpButtonAction();
		}

		if (PressedKeys[SDL_SCANCODE_A] || PressedKeys[SDL_SCANCODE_LEFT])
		{
			_gameContextManager->ExecuteDPadLeftButtonAction();
		}

		if (PressedKeys[SDL_SCANCODE_S] || PressedKeys[SDL_SCANCODE_DOWN])
		{
			_gameContextManager->ExecuteDPadDownButtonAction();
		}

		if (PressedKeys[SDL_SCANCODE_D] || PressedKeys[SDL_SCANCODE_RIGHT])
		{
			_gameContextManager->ExecuteDPadRightButtonAction();
		}

		if (PressedKeys[SDL_SCANCODE_SPACE] || PressedKeys[SDL_SCANCODE_RETURN] || PressedKeys[SDL_SCANCODE_C])
		{
			_gameContextManager->ExecuteAButtonAction();
		}

		if (PressedKeys[SDL_SCANCODE_BACKSPACE])
		{
			_gameContextManager->ExecuteBButtonAction();
		}

		if (PressedKeys[SDL_SCANCODE_X])
		{
			_gameContextManager->ExecuteXButtonAction();
		}

		if (PressedKeys[SDL_SCANCODE_2])
		{
			_gameContextManager->ExecuteYButtonAction();
		}

		if (PressedKeys[SDL_SCANCODE_ESCAPE])
		{
			_gameContextManager->ExecuteStartButtonAction();
		}

		// etc...
	}

	void InputKeyboardManager::CheckInputNotHold(SDL_Scancode scan) const
	{
		switch (scan)
		{
		case SDL_SCANCODE_W:
		case SDL_SCANCODE_UP:
			_gameContextManager->ExecuteDPadUpButtonAction();
			break;
		case SDL_SCANCODE_A:
		case SDL_SCANCODE_LEFT:
			_gameContextManager->ExecuteDPadLeftButtonAction();
			break;
		case SDL_SCANCODE_S:
		case SDL_SCANCODE_DOWN:
			_gameContextManager->ExecuteDPadDownButtonAction();
			break;
		case SDL_SCANCODE_D:
		case SDL_SCANCODE_RIGHT:
			_gameContextManager->ExecuteDPadRightButtonAction();
			break;
		case SDL_SCANCODE_SPACE:
		case SDL_SCANCODE_RETURN:
			_gameContextManager->ExecuteAButtonAction();
			break;
		case SDL_SCANCODE_BACKSPACE:
			_gameContextManager->ExecuteBButtonAction();
			break;
		case SDL_SCANCODE_ESCAPE:
			_gameContextManager->ExecuteStartButtonAction();
			break;
		}
	}

	void InputKeyboardManager::CheckReleaseInput(SDL_Scancode scan) const
	{
		switch (scan)
		{
		case SDL_SCANCODE_S:
		case SDL_SCANCODE_DOWN:
			_gameContextManager->ExecuteDPadDownButtonReleaseAction();
			break;
		}
	}
}
