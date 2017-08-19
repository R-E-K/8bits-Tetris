#pragma once
#include <SDL2/SDL.h>
#include <memory>
#include <vector>
#include "EntitiesConsts.h"
#include "TetrominoColorEnum.h"
#include "TetrominoShapeEnum.h"
#include "Tetromino.h"
#include <stack>
#include "LevelComponent.h"
#include "LinesRemovedCounterComponent.h"
#include "ScoreComponent.h"
#include "NextTetrominoComponent.h"
#include <algorithm>
#include "../core/window.h"
#include "../core/SDLDeletersFunctor.h"
#include "../core/SDLMainObjectsProvider.h"
#include "../graphics/ImageLoader.h"
#include "../core/Timer.h"

namespace REKTetrisGame
{

	class Board
	{
	public:
		Board();
		~Board();

		void Draw();
		void NewTetromino();
		void Update();

		bool IsGameOver() const;

		void MoveTetrominoToTheLeft();
		void MoveTetrominoToTheRight();
		void RotateTetrominoToLeftIfPossible();
		void RotateTetrominoToRightIfPossible();

		void MoveTetrominoDown();
		void MoveTetrominoDownRelease();

	private:

		// Properties
		const int MOVE_DOWN_TIMER_DEFAULT_FREQUENCY = 1000;

		std::unique_ptr<LevelComponent> _levelComponent;
		std::unique_ptr<LinesRemovedCounterComponent> _linesRemovedCounterComponent;
		std::unique_ptr<ScoreComponent> _scoreComponent;
		std::unique_ptr<NextTetrominoComponent> _nextTetrominoComponent;


		InputTimer _moveTetrominoToLeftOrRightTimer;
		Timer _tetrominoMovingDownTimer;
		int _moveDownTimerFrequency;
		bool _gameOver;

		std::stack<int> _tetrominoTileXPrevious;
		std::stack<int> _tetrominoTileYPrevious;

		std::shared_ptr<SDL_Texture> _lightBackgroundTexture;
		std::shared_ptr<SDL_Texture> _darkBackgroundTexture;
		std::unique_ptr<SDL_Texture, SdlDeleter> _borderBackgroundTexture;

		std::vector<std::shared_ptr<SDL_Texture>> _tetrominosTextures;

		int _backgroundTextureWidth;
		int _backgroundTextureHeight;

		// TODO : Maybe Boost Multi Array could be interesting
		std::vector<std::vector<TetrominoColorEnum>> _logicalTetrominosArray;

		std::unique_ptr<Tetromino> _currentTetromino;
		int _tetrominoPositionX;
		int _tetrominoPositionY;



		// Methods
			
		void SetTexturesBackground();
		void SetBorderBackground();
		std::shared_ptr<SDL_Texture> GetTetrominoTexture(std::string const& imageFilePath) const;
		void SetTetrominosTextures();

		void InitLogicalTetrominosArray();

		void DrawBorder() const;
		void DrawBackground() const;
		void DrawTetrominos() const;
		void DrawCurrentTetrominosOnBoard();

		TetrominoShapeEnum RandomlySelectTetrominoType();
		void SetTetrominoStartPosition(TetrominoShapeEnum tetrominoShape);

		bool CanMoveToLeft(std::vector<std::vector<int>> shapeToCheck);
		bool CanMoveToRight(std::vector<std::vector<int>> shapeToCheck);
		bool CanRotate(std::vector<std::vector<int>> shapeToCheck) const;
		bool CanRotateLeft() const;
		bool CanRotateRight() const;

		bool IsCollideBottom();

		void RemoveFullLines();
		bool isGameOverInternal();

		void SetTimers();

		void CheckLevel(int nbLinesJustRemoved);
		void UpdateScore(int nbLinesJustRemoved);
	};

}
