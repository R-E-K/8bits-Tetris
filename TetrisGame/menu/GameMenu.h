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
#include "../graphics/WindowConfiguration.h"
#include "../core/GameConfiguration.h"
#include "../input/KeyboardKeysFilePathConsts.h"
#include "../input/GamepadConfiguration.h"

namespace REKTetrisGame
{
	class GameMenu
	{
	public:
		GameMenu(std::shared_ptr<SoundManager> soundManager
			, std::shared_ptr<GameConfiguration> gameConfiguration
			, std::shared_ptr<GamepadConfiguration> gamepadConfiguration);
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
		std::map<Uint8, GameMenuItemEnum> _gameMenuItems;
		GameMenuItemEnum _selectedItem;
		Uint8 _selectedItemIndex;
		Uint8 _gameMenuLevel;

		std::unique_ptr<DrawTextService> _drawTextService;
		std::unique_ptr<DrawGameButtonLabelService> _drawGameButtonLabelService;
		std::shared_ptr<SoundManager> _soundManager;
		std::shared_ptr<GameConfiguration> _gameConfiguration;
		std::shared_ptr<GamepadConfiguration> _gamepadConfiguration;

		std::shared_ptr<SDL_Texture> _background;
		int _backgroundPositionX;
		int _backgroundPositionY;
		int _backgroundTextureWidth;
		int _backgroundTextureHeight;

		std::shared_ptr<SDL_Texture> CreateBackground(SDL_Rect& gameMenuPosition);
		void DrawMainMenu(std::shared_ptr<Board> board);
		void DrawItemsMenu(std::shared_ptr<Board> board) const;
		void DrawItemMenu(std::string const& itemMenuName, GameMenuItemEnum gameMenuItem, int x, int y) const;

		void DrawCredits();

		void AddBackButton() const;
		void AddValidButton() const;
	};
}

