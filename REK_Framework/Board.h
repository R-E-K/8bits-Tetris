#pragma once
#include <SDL2/SDL.h>
#include <memory>
#include <vector>
#include "SDLDeletersFunctor.h"
#include "window.h"
#include "SDLMainObjectsProvider.h"
#include "TetrominoColorEnum.h"

namespace REKFramework
{
	class Board
	{
	public:
		Board();
		~Board();

		void Draw();

	private:

		const Uint8 NB_COLUMNS = 10;
		const Uint8 NB_ROWS = 18;
		const int BORDER_THICKNESS = 5;

		std::shared_ptr<SDL_Texture> lightBackgroundTexture;
		std::shared_ptr<SDL_Texture> darkBackgroundTexture;
		std::unique_ptr<SDL_Texture, SdlDeleter> borderBackgroundTexture;

		std::vector<std::shared_ptr<SDL_Texture>> TetrominosTextures;

		int backgroundTextureWidth;
		int backgroundTextureHeight;

		// TODO : Maybe Boost Multi Array could be interesting
		std::vector<std::vector<TetrominoColorEnum>> logicalTetrominosArray;

		void SetTexturesBackground();
		void SetBorderBackground();
		std::shared_ptr<SDL_Texture> GetTetrominoTexture(std::string const& imageFilePath);
		void SetTetrominosTextures();

		void InitLogicalTetrominosArray();

		void DrawBorder() const;
		void DrawBackground() const;
		void DrawTetrominos() const;
	};

}
