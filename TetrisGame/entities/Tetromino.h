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

		TetrominoShapeEnum Shape;
		TetrominoColorEnum Color;
		int ShapeIndex;

		InputTimer RotateTimer;

		std::vector<std::vector<std::vector<int>>> TetrominoShapesArray;
		std::vector<std::vector<int>> CurrentTetrominoShape;

		void SetShapes();
		void SetColor();
	};
}

