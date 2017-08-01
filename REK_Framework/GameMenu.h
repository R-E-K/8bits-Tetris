#pragma once
#include "GameMenuItemEnum.h"
#include <map>
#include <SDL2/SDL.h>
#include "window.h"
#include "SDLMainObjectsProvider.h"
#include "GamepadButtonsFilePathConsts.h"
#include "DrawTextService.h"
#include "DrawGameButtonLabelService.h"
#include "SoundManager.h"

namespace REKFramework
{
	class GameMenu
	{
	public:
		GameMenu(std::shared_ptr<SoundManager> soundManager);
		~GameMenu();

		void Draw();

		void NavigateDown();
		void NavigateUp();
		void SelectItemMenu();
		void MenuBack();
		bool MustDestroyGameMenuOnSelect() const;
		bool MustDestroyGameMenuOnBack() const;

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

		std::shared_ptr<SDL_Texture> CreateBackground(SDL_Rect& gameMenuPosition) const;
		void DrawMainMenu();
		void DrawItemsMenu() const;
		void DrawItemMenu(std::string const& itemMenuName, GameMenuItemEnum gameMenuItem, int x, int y) const;

		void DrawCredits();

		void AddBackButton() const;
		void AddValidButton() const;
	};
}

