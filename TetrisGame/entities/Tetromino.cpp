#include "Tetromino.h"

namespace REKFramework
{

	Tetromino::Tetromino(TetrominoShapeEnum tetrominoShape)
	{
		Shape = tetrominoShape;
		SetShapes();
		SetColor();
		ShapeIndex = 0;
		CurrentTetrominoShape = TetrominoShapesArray[ShapeIndex];

		RotateTimer.SetInputRepeatFrequency(500);
		RotateTimer.SetStartHoldInputDownDelay(500);
		RotateTimer.SetDelay(200);
	}

	Tetromino::~Tetromino()
	{
	}

	std::vector<std::vector<int>> Tetromino::GetTetrominoCurrentShape() const
	{
		return CurrentTetrominoShape;
	}

	TetrominoColorEnum Tetromino::GetColor() const
	{
		return Color;
	}

	TetrominoShapeEnum Tetromino::GetShape() const
	{
		return Shape;
	}

	void Tetromino::RotateLeft()
	{
		RotateTimer.Execute([&]()
		{
			if (ShapeIndex == 0)
			{
				ShapeIndex = TetrominoShapesArray.size();
			}
			ShapeIndex--;
			CurrentTetrominoShape = TetrominoShapesArray[ShapeIndex];
		});
	}

	void Tetromino::RotateRight()
	{
		RotateTimer.Execute([&]()
		{
			if (ShapeIndex == TetrominoShapesArray.size() - 1)
			{
				ShapeIndex = -1;
			}
			ShapeIndex++;
			CurrentTetrominoShape = TetrominoShapesArray[ShapeIndex];
		});
	}

	void Tetromino::SetRotateTimerDelay(int delay)
	{
		RotateTimer.SetDelay(delay);
	}

	std::vector<std::vector<int>> Tetromino::GetNextShape()
	{
		if (ShapeIndex == TetrominoShapesArray.size() - 1)
		{
			return TetrominoShapesArray[0];
		}
		else
		{
			return TetrominoShapesArray[ShapeIndex + 1];
		}
	}

	std::vector<std::vector<int>> Tetromino::GetPreviousShape()
	{
		if (ShapeIndex == 0)
		{
			return TetrominoShapesArray[TetrominoShapesArray.size() - 1];
		}
		else
		{
			return TetrominoShapesArray[ShapeIndex - 1];
		}
	}

	void Tetromino::SetShapes()
	{
		switch (Shape)
		{
		case TetrominoShapeEnum::I:
			TetrominoShapesArray = { 
				{
					{ 7, 7, 7, 7 },
					{ 7, 7, 7, 7 },
					{ 2, 2, 2, 2 },
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
