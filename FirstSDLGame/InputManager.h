#pragma once
#include <SDL2/SDL.h>
#include "InputKeyboardManager.h"
#include "InputGamepadManager.h"
#include <vector>
#include <algorithm>
#include "GamepadConfiguration.h"


class InputManager
{
public:
	InputManager(GameContextManager* gameContextManager);
	~InputManager();

	void CheckInput(SDL_Event* e, bool* quitGame);
	
private:
	SDL_Event* PressedInput;
	InputKeyboardManager* keyboardManager;
	InputGamepadManager* gamepadManager;
	GamepadConfiguration* gamepadCnfg;
	GameContextManager* gameContextMngr;

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

