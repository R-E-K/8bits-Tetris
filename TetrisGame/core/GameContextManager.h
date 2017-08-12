#pragma once
#include "GameContextEnum.h"
#include <SDL2/SDL.h>
#include "../menu/GameMenu.h"
#include "../entities/Board.h"
#include "../graphics/DrawPictureManager.h"

namespace REKFramework
{
	class GameContextManager
	{
	public:
		GameContextManager();
		~GameContextManager();

		static GameContextEnum CurrentGameContext;

		static bool IsGamePaused();

		void SetGameMenu(std::shared_ptr<GameMenu> gMenu);
		void SetBoardGame(std::shared_ptr<Board> gBoard);

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


		void ExecuteDPadDownButtonReleaseAction();

	private:
		std::shared_ptr<GameMenu> gameMenu;
		std::shared_ptr<Board> boardGame;

		std::unique_ptr<DrawPictureManager> DrawPictureMngr;

		void CloseGameMenu();

	};
}

