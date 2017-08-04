#pragma once
#include "TetrominoColorEnum.h"
#include <vector>
#include "TetrominoShapeEnum.h"
#include "InputTimer.h"

namespace REKFramework
{
	class Tetromino
	{
	public:
		Tetromino(TetrominoShapeEnum tetrominoShape);
		~Tetromino();

		std::vector<std::vector<int>> GetTetromino() const;
		TetrominoColorEnum GetColor() const;

		void RotateLeft();
		void RotateRight();

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

