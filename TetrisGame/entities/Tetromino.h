#pragma once
#include "TetrominoColorEnum.h"
#include <vector>
#include "TetrominoShapeEnum.h"
#include "../core/InputTimer.h"

namespace REKTetrisGame
{
	class Tetromino
	{
	public:
		Tetromino(TetrominoShapeEnum tetrominoShape);
		~Tetromino();

		std::vector<std::vector<int>> GetTetrominoCurrentShape() const;
		TetrominoColorEnum GetColor() const;
		TetrominoShapeEnum GetShape() const;

		void RotateLeft();
		void RotateRight();

		void SetRotateTimerDelay(int delay);

		std::vector<std::vector<int>> GetNextShape();
		std::vector<std::vector<int>> GetPreviousShape();

	private:

		TetrominoShapeEnum _shape;
		TetrominoColorEnum _color;
		int _shapeIndex;

		InputTimer _rotateTimer;

		std::vector<std::vector<std::vector<int>>> _tetrominoShapesArray;
		std::vector<std::vector<int>> _currentTetrominoShape;

		void SetShapes();
		void SetColor();
	};
}

