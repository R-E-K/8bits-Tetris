#include "Tetromino.h"

namespace REKFramework
{

	Tetromino::Tetromino(TetrominoShapeEnum tetrominoShape)
	{
		Shape = tetrominoShape;
		SetShapes();
		SetColor();
		CurrentTetrominoShape = TetrominoShapesArray[0];
	}

	Tetromino::~Tetromino()
	{
	}

	std::vector<std::vector<int>> Tetromino::GetTetromino() const
	{
		return CurrentTetrominoShape;
	}

	TetrominoColorEnum Tetromino::GetColor() const
	{
		return Color;
	}

	void Tetromino::SetShapes()
	{
		switch (Shape)
		{
		case TetrominoShapeEnum::I:
			TetrominoShapesArray = { 
				{
					{ 7, 7, 7, 7 },
					{ 2, 2, 2, 2 },
					{ 7, 7, 7, 7 },
					{ 7, 7, 7, 7 }
				},
				{
					{ 7, 7, 2, 7 },
					{ 7, 7, 2, 7 },
					{ 7, 7, 2, 7 },
					{ 7, 7, 2, 7 }
				}
			};
			break;
		case TetrominoShapeEnum::J:
			TetrominoShapesArray = {
				{
					{ 7, 7, 7 },
					{ 0, 0, 0 },
					{ 7, 7, 0 }
				},
				{
					{ 7, 7, 0 },
					{ 7, 7, 0 },
					{ 7, 0, 0 }
				},
				{
					{ 0, 7, 7 },
					{ 0, 0, 0 },
					{ 7, 7, 7 }
				},
				{
					{ 7, 0, 0 },
					{ 7, 0, 7 },
					{ 7, 0, 7 }
				}
			};
			break;
		case TetrominoShapeEnum::L:
			TetrominoShapesArray = {
				{
					{ 7, 7, 7 },
					{ 1, 1, 1 },
					{ 1, 7, 7 }
				},
				{
					{ 1, 1, 7 },
					{ 7, 1, 7 },
					{ 7, 1, 7 }
				},
				{
					{ 7, 7, 1 },
					{ 1, 1, 1 },
					{ 7, 7, 7 }
				},
				{
					{ 7, 1, 7 },
					{ 7, 1, 7 },
					{ 7, 1, 1 }
				}
			};
			break;
		case TetrominoShapeEnum::O:
			TetrominoShapesArray = {
				{
					{ 5, 5 },
					{ 5, 5 }
				}
			};
			break;
		case TetrominoShapeEnum::S:
			TetrominoShapesArray = {
				{
					{ 7, 7, 7 },
					{ 7, 3, 3 },
					{ 3, 3, 7 }
				},
				{
					{ 3, 7, 7 },
					{ 3, 3, 7 },
					{ 7, 3, 7 }
				}
			};
			break;
		case TetrominoShapeEnum::Z:
			TetrominoShapesArray = {
				{
					{ 7, 7, 7 },
					{ 6, 6, 7 },
					{ 7, 6, 6 }
				},
				{
					{ 7, 7, 6 },
					{ 7, 6, 6 },
					{ 7, 6, 7 }
				}
			};
			break;
		case TetrominoShapeEnum::T:
			TetrominoShapesArray = {
				{
					{ 7, 7, 7 },
					{ 4, 4, 4 },
					{ 7, 4, 7 }
				},
				{
					{ 7, 4, 7 },
					{ 4, 4, 7 },
					{ 7, 4, 7 }
				},
				{
					{ 7, 4, 7 },
					{ 4, 4, 4 },
					{ 7, 7, 7 }
				},
				{
					{ 7, 4, 7 },
					{ 7, 4, 4 },
					{ 7, 4, 7 }
				}
			};
			break;
		}
	}

	void Tetromino::SetColor()
	{
		switch (Shape)
		{
			case TetrominoShapeEnum::I:
				Color = TetrominoColorEnum::GREEN;
				break;
			case TetrominoShapeEnum::J:
				Color = TetrominoColorEnum::BLUE;
				break;
			case TetrominoShapeEnum::L:
				Color = TetrominoColorEnum::BROWN;
				break;
			case TetrominoShapeEnum::O:
				Color = TetrominoColorEnum::RED;
				break;
			case TetrominoShapeEnum::S:
				Color = TetrominoColorEnum::ORANGE;
				break;
			case TetrominoShapeEnum::T:
				Color = TetrominoColorEnum::PURPLE;
				break;
			case TetrominoShapeEnum::Z:
				Color = TetrominoColorEnum::YELLOW;
				break;
		}
	}
}
