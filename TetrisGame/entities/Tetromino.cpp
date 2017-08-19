#include "Tetromino.h"

namespace REKTetrisGame
{

	Tetromino::Tetromino(TetrominoShapeEnum tetrominoShape)
	{
		_shape = tetrominoShape;
		SetShapes();
		SetColor();
		_shapeIndex = 0;
		_currentTetrominoShape = _tetrominoShapesArray[_shapeIndex];

		_rotateTimer.SetInputRepeatFrequency(500);
		_rotateTimer.SetStartHoldInputDownDelay(500);
		_rotateTimer.SetDelay(200);
	}

	Tetromino::~Tetromino()
	{
	}

	std::vector<std::vector<int>> Tetromino::GetTetrominoCurrentShape() const
	{
		return _currentTetrominoShape;
	}

	TetrominoColorEnum Tetromino::GetColor() const
	{
		return _color;
	}

	TetrominoShapeEnum Tetromino::GetShape() const
	{
		return _shape;
	}

	void Tetromino::RotateLeft()
	{
		_rotateTimer.Execute([&]()
		{
			if (_shapeIndex == 0)
			{
				_shapeIndex = _tetrominoShapesArray.size();
			}
			_shapeIndex--;
			_currentTetrominoShape = _tetrominoShapesArray[_shapeIndex];
		});
	}

	void Tetromino::RotateRight()
	{
		_rotateTimer.Execute([&]()
		{
			if (_shapeIndex == _tetrominoShapesArray.size() - 1)
			{
				_shapeIndex = -1;
			}
			_shapeIndex++;
			_currentTetrominoShape = _tetrominoShapesArray[_shapeIndex];
		});
	}

	void Tetromino::SetRotateTimerDelay(int delay)
	{
		_rotateTimer.SetDelay(delay);
	}

	std::vector<std::vector<int>> Tetromino::GetNextShape()
	{
		if (_shapeIndex == _tetrominoShapesArray.size() - 1)
		{
			return _tetrominoShapesArray[0];
		}
		else
		{
			return _tetrominoShapesArray[_shapeIndex + 1];
		}
	}

	std::vector<std::vector<int>> Tetromino::GetPreviousShape()
	{
		if (_shapeIndex == 0)
		{
			return _tetrominoShapesArray[_tetrominoShapesArray.size() - 1];
		}
		else
		{
			return _tetrominoShapesArray[_shapeIndex - 1];
		}
	}

	void Tetromino::SetShapes()
	{
		switch (_shape)
		{
		case TetrominoShapeEnum::I:
			_tetrominoShapesArray = { 
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
			_tetrominoShapesArray = {
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
			_tetrominoShapesArray = {
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
			_tetrominoShapesArray = {
				{
					{ 5, 5 },
					{ 5, 5 }
				}
			};
			break;
		case TetrominoShapeEnum::S:
			_tetrominoShapesArray = {
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
			_tetrominoShapesArray = {
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
			_tetrominoShapesArray = {
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
		switch (_shape)
		{
			case TetrominoShapeEnum::I:
				_color = TetrominoColorEnum::GREEN;
				break;
			case TetrominoShapeEnum::J:
				_color = TetrominoColorEnum::BLUE;
				break;
			case TetrominoShapeEnum::L:
				_color = TetrominoColorEnum::BROWN;
				break;
			case TetrominoShapeEnum::O:
				_color = TetrominoColorEnum::RED;
				break;
			case TetrominoShapeEnum::S:
				_color = TetrominoColorEnum::ORANGE;
				break;
			case TetrominoShapeEnum::T:
				_color = TetrominoColorEnum::PURPLE;
				break;
			case TetrominoShapeEnum::Z:
				_color = TetrominoColorEnum::YELLOW;
				break;
		}
	}
}
