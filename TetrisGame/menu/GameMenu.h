#pragma once
#include "GameMenuItemEnum.h"
#include <map>
#include <SDL2/SDL.h>
#include <memory>
#include "../sounds/SoundManager.h"
#include "../graphics/DrawTextService.h"
#include "../graphics/DrawGameButtonLabelService.h"
#include "../core/window.h"
#include "../input/GamepadButtonsFilePathConsts.h"
#include "../core/GameContextEnum.h"
#include "../entities/Board.h"

namespace REKFramework
{
	class GameMenu
	{
	public:
		GameMenu(std::shared_ptr<SoundManager> soundManager);
		~GameMenu();

		void Draw(std::shared_ptr<Board> board);

		void NavigateDown();
		void NavigateUp();
		void SelectItemMenu();
		void MenuBack();
		bool MustDestroyGameMenuOnSelect() const;
		bool MustDestroyGameMenuOnBack(std::shared_ptr<Board> board) const;

		GameMenuItemEnum GetLastItemMenuSelected() const;

	private:
		std::map<Uint8, GameMenuItemEnum> gameMenuItems;
		GameMenuItemEnum selectedItem;
		Uint8 selectedItemIndex;
		Uint8 GameMenuLevel;

		std::unique_ptr<DrawTextService> drawTextSrvc;
		std::unique_ptr<DrawGameButtonLabelService> DrawGameButtonLabelSrvc;
		std::shared_ptr<SoundManager> soundMngr;

		std::shared_ptr<SDL_Texture> background;
		int backgroundPositionX;
		int backgroundPositionY;
		int backgroundTextureWidth;
		int backgroundTextureHeight;

		std::shared_ptr<SDL_Texture> CreateBackground(SDL_Rect& gameMenuPosition);
		void DrawMainMenu(std::shared_ptr<Board> board);
		void DrawItemsMenu(std::shared_ptr<Board> board) const;
		void DrawItemMenu(std::string const& itemMenuName, GameMenuItemEnum gameMenuItem, int x, int y) const;

		void DrawCredits();

		void AddBackButton() const;
		void AddValidButton() const;
	};
}

