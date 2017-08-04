#pragma once
#include <SDL2/SDL.h>
#include <memory>
#include <vector>
#include "SDLDeletersFunctor.h"
#include "window.h"
#include "SDLMainObjectsProvider.h"
#include "TetrominoColorEnum.h"
#include "TetrominoShapeEnum.h"
#include "Tetromino.h"
#include <stack>
#include "InputTimer.h"

namespace REKFramework
{

	class Board
	{
	public:
		Board();
		~Board();

		void Draw() const;
		void NewTetromino();
		void Update();

		void MoveTetrominoToTheLeft();
		void MoveTetrominoToTheRight();
		void RotateTetrominoToLeftIfPossible();
		void RotateTetrominoToRightIfPossible();

	private:

		const Uint8 NB_COLUMNS = 10;
		const Uint8 NB_ROWS = 18;
		const int BORDER_THICKNESS = 5;

		InputTimer MoveTetrominoToLeftOrRightTimer;

		std::stack<int> TetrominoTileXPrevious;
		std::stack<int> TetrominoTileYPrevious;

		std::shared_ptr<SDL_Texture> lightBackgroundTexture;
		std::shared_ptr<SDL_Texture> darkBackgroundTexture;
		std::unique_ptr<SDL_Texture, SdlDeleter> borderBackgroundTexture;

		std::vector<std::shared_ptr<SDL_Texture>> TetrominosTextures;

		int backgroundTextureWidth;
		int backgroundTextureHeight;

		// TODO : Maybe Boost Multi Array could be interesting
		std::vector<std::vector<TetrominoColorEnum>> logicalTetrominosArray;

		std::unique_ptr<Tetromino> CurrentTetromino;
		int TetrominoPositionX;
		int TetrominoPositionY;
			
		void SetTexturesBackground();
		void SetBorderBackground();
		std::shared_ptr<SDL_Texture> GetTetrominoTexture(std::string const& imageFilePath) const;
		void SetTetrominosTextures();

		void InitLogicalTetrominosArray();

		void PlaceCurrentTetrominosOnBoard();

		void DrawBorder() const;
		void DrawBackground() const;
		void DrawTetrominos() const;

		TetrominoShapeEnum RandomlySelectTetrominoType();
		void SetTetrominoStartPosition(TetrominoShapeEnum tetrominoShape);

		bool CanMoveToLeft(std::vector<std::vector<int>> shapeToCheck);
		bool CanMoveToRight(std::vector<std::vector<int>> shapeToCheck);
		bool CanRotate(std::vector<std::vector<int>> shapeToCheck) const;
		bool CanRotateLeft();
		bool CanRotateRight();

		void SetTimers();
	};

}
