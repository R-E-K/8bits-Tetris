#pragma once
#include "GameContext.h"
#include <SDL2/SDL.h>
#include "DrawPictureManager.h"
#include "GameMenu.h"

namespace REKFramework
{
	class GameContextManager
	{
	public:
		GameContextManager();
		~GameContextManager();

		GameContext currentGameContext;

		void SetGameMenu(GameMenu* gMenu);

		void ExecuteAButtonAction();
		void ExecuteBButtonAction();
		void ExecuteXButtonAction();
		void ExecuteYButtonAction();
		void ExecuteLBButtonAction();
		void ExecuteRBButtonAction();
		void ExecuteDPadDownButtonAction();
		void ExecuteDPadUpButtonAction();
		void ExecuteDPadLeftButtonAction();
		void ExecuteDPadRightButtonAction();
		void ExecuteL3ButtonAction();
		void ExecuteR3ButtonAction();
		void ExecuteStartButtonAction();
		void ExecuteBackButtonAction();

		void ExecuteLTTriggerAction();
		void ExecuteRTTriggerAction();

	private:
		GameMenu* gameMenu;

		std::unique_ptr<DrawPictureManager> DrawPictureMngr;

		void CloseGameMenu();

	};
}

