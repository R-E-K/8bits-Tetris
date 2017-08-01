#pragma once
#include "GameContextEnum.h"
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

		GameContextEnum currentGameContext;

		void SetGameMenu(std::shared_ptr<GameMenu> gMenu);

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
		std::shared_ptr<GameMenu> gameMenu;

		std::unique_ptr<DrawPictureManager> DrawPictureMngr;

		void CloseGameMenu();

	};
}

