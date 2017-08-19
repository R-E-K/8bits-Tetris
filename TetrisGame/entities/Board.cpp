#include "Board.h"


namespace REKTetrisGame
{
	Board::Board()
	{
		// It will be a square
		_backgroundTextureWidth = (SCREEN_HEIGHT * (85.0 / 100.0)) / EntitiesConsts::NB_ROWS;
		_backgroundTextureHeight = (SCREEN_HEIGHT * (85.0 / 100.0)) / EntitiesConsts::NB_ROWS;

		_gameOver = false;
		_moveDownTimerFrequency = MOVE_DOWN_TIMER_DEFAULT_FREQUENCY;

		SetBorderBackground();
		SetTexturesBackground();
		SetTetrominosTextures();
		InitLogicalTetrominosArray();
		SetTimers();

		TetrominoShapeEnum selectedShape = RandomlySelectTetrominoType();
		_currentTetromino = std::make_unique<Tetromino>(selectedShape);
		SetTetrominoStartPosition(selectedShape);
		_moveTetrominoToLeftOrRightTimer.SetDelay(200);
		_tetrominoMovingDownTimer.SetDelay(200);
		_currentTetromino->SetRotateTimerDelay(200);

		_levelComponent = std::make_unique<LevelComponent>(20.0, 10.0);
		_linesRemovedCounterComponent = std::make_unique<LinesRemovedCounterComponent>(20.0, 10.0);
		_scoreComponent = std::make_unique<ScoreComponent>(85.0, 8.0);
		_nextTetrominoComponent = std::make_unique<NextTetrominoComponent>(20.0, 20.0, RandomlySelectTetrominoType());
	}


	Board::~Board()
	{
	}

	void Board::Draw()
	{
		DrawBorder();
		DrawBackground();
		DrawTetrominos();
		DrawCurrentTetrominosOnBoard();

		_levelComponent->Draw();
		_linesRemovedCounterComponent->Draw();
		_scoreComponent->Draw();
		_nextTetrominoComponent->Draw();
	}

	void Board::NewTetromino()
	{
		_currentTetromino = _nextTetrominoComponent->PopTetromino();
		_nextTetrominoComponent->SetTetromino(RandomlySelectTetrominoType());
		SetTetrominoStartPosition(_currentTetromino->GetShape());

		_moveTetrominoToLeftOrRightTimer.SetDelay(200);
		_tetrominoMovingDownTimer.SetDelay(200);
		_currentTetromino->SetRotateTimerDelay(200);

		if (isGameOverInternal())
		{
			_gameOver = true;
		}
	}

	void Board::Update()
	{

		// Need to be draw here to have the last shape
		DrawCurrentTetrominosOnBoard();

		_tetrominoMovingDownTimer.Execute([&]()
		{
			if (!IsCollideBottom())
			{
				_tetrominoPositionY++;
			}
			else
			{
				// Clear Stacks
				// Unfortunately, extension methods don't exist in C++
				while (!_tetrominoTileXPrevious.empty())
				{
					_tetrominoTileXPrevious.pop();
				}

				while (!_tetrominoTileYPrevious.empty())
				{
					_tetrominoTileYPrevious.pop();
				}

				RemoveFullLines();

				NewTetromino();
			}
		});
	}

	bool Board::IsGameOver() const
	{
		return _gameOver;
	}

	void Board::MoveTetrominoToTheLeft()
	{
		if (CanMoveToLeft(_currentTetromino->GetTetrominoCurrentShape()))
		{
			_moveTetrominoToLeftOrRightTimer.Execute([&]()
			{
				_tetrominoPositionX--;
			});
		}
	}

	void Board::MoveTetrominoToTheRight()
	{
		if (CanMoveToRight(_currentTetromino->GetTetrominoCurrentShape()))
		{
			_moveTetrominoToLeftOrRightTimer.Execute([&]()
			{
				_tetrominoPositionX++;
			});
		}
	}

	void Board::RotateTetrominoToLeftIfPossible()
	{
		if (CanRotateLeft())
		{
			_currentTetromino->RotateLeft();
		}
	}

	void Board::RotateTetrominoToRightIfPossible()
	{
		if (CanRotateRight())
		{
			_currentTetromino->RotateRight();
		}
	}

	void Board::MoveTetrominoDown()
	{
		_tetrominoMovingDownTimer.SetRepeatFrequency(50);
	}

	void Board::MoveTetrominoDownRelease()
	{
		_tetrominoMovingDownTimer.SetRepeatFrequency(_moveDownTimerFrequency);
	}

	void Board::SetTexturesBackground()
	{
		auto surfaceLight = std::unique_ptr<SDL_Surface, SdlDeleter>(
			SDL_CreateRGBSurface(0, _backgroundTextureWidth, _backgroundTextureHeight, 32, 0, 0, 0, 0)
			, SdlDeleter());

		SDL_FillRect(surfaceLight.get(), nullptr, SDL_MapRGB(surfaceLight->format, 215, 215, 215));

		_lightBackgroundTexture = std::shared_ptr<SDL_Texture>(
			SDL_CreateTextureFromSurface(SDLMainObjectsProvider::GetRendererRawPointer(), surfaceLight.get()),
			SdlDeleter()
			);


		auto darkLight = std::unique_ptr<SDL_Surface, SdlDeleter>(
			SDL_CreateRGBSurface(0, _backgroundTextureWidth, _backgroundTextureHeight, 32, 0, 0, 0, 0)
			, SdlDeleter());

		SDL_FillRect(darkLight.get(), nullptr, SDL_MapRGB(darkLight->format, 171, 171, 171));

		_darkBackgroundTexture = std::shared_ptr<SDL_Texture>(
			SDL_CreateTextureFromSurface(SDLMainObjectsProvider::GetRendererRawPointer(), darkLight.get()),
			SdlDeleter()
			);
	}

	void Board::SetBorderBackground()
	{
		auto surfaceBorder = std::unique_ptr<SDL_Surface, SdlDeleter>(
			SDL_CreateRGBSurface(0, _backgroundTextureWidth * EntitiesConsts::NB_COLUMNS, _backgroundTextureHeight * EntitiesConsts::NB_ROWS, 32, 0, 0, 0, 0)
			, SdlDeleter());

		SDL_FillRect(surfaceBorder.get(), nullptr, SDL_MapRGB(surfaceBorder->format, 0, 0, 0));

		_borderBackgroundTexture = std::unique_ptr<SDL_Texture, SdlDeleter>(
			SDL_CreateTextureFromSurface(SDLMainObjectsProvider::GetRendererRawPointer(), surfaceBorder.get()),
			SdlDeleter()
			);
	}

	std::shared_ptr<SDL_Texture> Board::GetTetrominoTexture(std::string const& imageFilePath) const
	{
		auto tetrominoSurface = ImageLoader::GetImageWithoutTransparency(imageFilePath);

		return std::shared_ptr<SDL_Texture>(
			SDL_CreateTextureFromSurface(SDLMainObjectsProvider::GetRendererRawPointer(), tetrominoSurface.get()),
			SdlDeleter()
			);
	}

	void Board::SetTetrominosTextures()
	{
		_tetrominosTextures.resize(7);
		_tetrominosTextures[0] = GetTetrominoTexture("resources/graphics/tetrominos/blue.png");
		_tetrominosTextures[1] = GetTetrominoTexture("resources/graphics/tetrominos/brown.png");
		_tetrominosTextures[2] = GetTetrominoTexture("resources/graphics/tetrominos/green.png");
		_tetrominosTextures[3] = GetTetrominoTexture("resources/graphics/tetrominos/orange.png");
		_tetrominosTextures[4] = GetTetrominoTexture("resources/graphics/tetrominos/purple.png");
		_tetrominosTextures[5] = GetTetrominoTexture("resources/graphics/tetrominos/red.png");
		_tetrominosTextures[6] = GetTetrominoTexture("resources/graphics/tetrominos/yellow.png");
	}

	void Board::InitLogicalTetrominosArray()
	{
		// Set up sizes. (HEIGHT x WIDTH)
		_logicalTetrominosArray.resize(EntitiesConsts::NB_ROWS);
		for (int i = 0; i < EntitiesConsts::NB_ROWS; ++i)
			_logicalTetrominosArray[i].resize(EntitiesConsts::NB_COLUMNS);

		for (int i = 0; i < EntitiesConsts::NB_ROWS; i++)
		{
			for (int j = 0; j < EntitiesConsts::NB_COLUMNS; j++)
			{
				_logicalTetrominosArray[i][j] = TetrominoColorEnum::NONE;
			}
		}
	}

	void Board::DrawCurrentTetrominosOnBoard()
	{
		if (!_tetrominoTileXPrevious.empty())
		{
			for (int i = 0; i < _tetrominoTileYPrevious.size(); i++) // Y Axis
			{
				int x = _tetrominoTileXPrevious.top();
				_tetrominoTileXPrevious.pop();

				int y = _tetrominoTileYPrevious.top();
				_tetrominoTileYPrevious.pop();

				_logicalTetrominosArray[y][x] = TetrominoColorEnum::NONE;
			}
		}

		auto Tetromino = _currentTetromino->GetTetrominoCurrentShape();

		int tetrominoTileX = _tetrominoPositionX - 1;
		int tetrominoTileY = _tetrominoPositionY - 1;

		for (int i = 0; i < Tetromino.size(); i++) // Y Axis
		{
			tetrominoTileY++;

			tetrominoTileX = _tetrominoPositionX - 1;
			for (int j = 0; j < Tetromino[i].size(); j++) // X Axis
			{
				tetrominoTileX++;

				if (Tetromino[i][j] != static_cast<int>(TetrominoColorEnum::NONE))
				{
					_logicalTetrominosArray[tetrominoTileY][tetrominoTileX] = _currentTetromino->GetColor();
					_tetrominoTileYPrevious.push(tetrominoTileY);
					_tetrominoTileXPrevious.push(tetrominoTileX);
				}
			}
		}
	}

	void Board::DrawBorder() const
	{
		SDL_Rect backgroundTilePosition;
		backgroundTilePosition.x = (SCREEN_WIDTH / 2) - ((_backgroundTextureWidth * EntitiesConsts::NB_COLUMNS) / 2) + _backgroundTextureWidth - EntitiesConsts::BORDER_THICKNESS;
		backgroundTilePosition.y = SCREEN_HEIGHT * (12.0 / 100.0) - EntitiesConsts::BORDER_THICKNESS; // Start at 10% from top
		backgroundTilePosition.w = (_backgroundTextureWidth * EntitiesConsts::NB_COLUMNS) + (EntitiesConsts::BORDER_THICKNESS * 2);
		backgroundTilePosition.h = (_backgroundTextureHeight * EntitiesConsts::NB_ROWS) + (EntitiesConsts::BORDER_THICKNESS * 2);

		SDL_RenderCopy(SDLMainObjectsProvider::GetRendererRawPointer()
			, _borderBackgroundTexture.get()
			, nullptr, &backgroundTilePosition);
	}

	void Board::DrawBackground() const
	{
		int backgroundTileXInitPosition = (SCREEN_WIDTH / 2) - ((_backgroundTextureWidth * EntitiesConsts::NB_COLUMNS) / 2);

		SDL_Rect backgroundTilePosition;
		backgroundTilePosition.x = backgroundTileXInitPosition - _backgroundTextureWidth;
		backgroundTilePosition.y = SCREEN_HEIGHT * (12.0 / 100.0) - _backgroundTextureHeight; // Start at 10% from top
		backgroundTilePosition.w = _backgroundTextureWidth;
		backgroundTilePosition.h = _backgroundTextureHeight;

		bool isLight;

		for (int i = 0; i < EntitiesConsts::NB_ROWS; i++)
		{
			backgroundTilePosition.y += _backgroundTextureHeight;
			backgroundTilePosition.x = backgroundTileXInitPosition;

			// First column is always light
			isLight = true;
			for (int j = 0; j < EntitiesConsts::NB_COLUMNS; j++)
			{
				backgroundTilePosition.x += _backgroundTextureWidth;

				SDL_RenderCopy(SDLMainObjectsProvider::GetRendererRawPointer()
					, isLight ? _lightBackgroundTexture.get() : _darkBackgroundTexture.get()
					, nullptr, &backgroundTilePosition);

				isLight = !isLight;
			}
		}
	}

	void Board::DrawTetrominos() const
	{
		int backgroundTileXInitPosition = (SCREEN_WIDTH / 2) - ((_backgroundTextureWidth * EntitiesConsts::NB_COLUMNS) / 2);

		SDL_Rect backgroundTilePosition;
		backgroundTilePosition.x = backgroundTileXInitPosition - _backgroundTextureWidth;
		backgroundTilePosition.y = SCREEN_HEIGHT * (12.0 / 100.0) - _backgroundTextureHeight; // Start at 10% from top
		backgroundTilePosition.w = _backgroundTextureWidth;
		backgroundTilePosition.h = _backgroundTextureHeight;

		for (int i = 0; i < EntitiesConsts::NB_ROWS; i++)
		{
			backgroundTilePosition.y += _backgroundTextureHeight;
			backgroundTilePosition.x = backgroundTileXInitPosition;

			for (int j = 0; j < EntitiesConsts::NB_COLUMNS; j++)
			{
				backgroundTilePosition.x += _backgroundTextureWidth;

				if (_logicalTetrominosArray[i][j] != TetrominoColorEnum::NONE)
				{
					SDL_RenderCopy(SDLMainObjectsProvider::GetRendererRawPointer()
						, _tetrominosTextures[static_cast<int>(_logicalTetrominosArray[i][j])].get()
						, nullptr, &backgroundTilePosition);
				}
			}
		}
	}

	TetrominoShapeEnum Board::RandomlySelectTetrominoType()
	{
		// Generate a number between 0 and 99
		int rng = rand() % 100;

		if (rng < 10)
			return TetrominoShapeEnum::I;
		else if (rng < 25)
			return TetrominoShapeEnum::J;
		else if (rng < 40)
			return TetrominoShapeEnum::L;
		else if (rng < 55)
			return TetrominoShapeEnum::O;
		else if (rng < 70)
			return TetrominoShapeEnum::S;
		else if (rng < 85)
			return TetrominoShapeEnum::T;
		else if (rng < 100)
			return TetrominoShapeEnum::Z;
	}

	void Board::SetTetrominoStartPosition(TetrominoShapeEnum tetrominoShape)
	{
		_tetrominoPositionY = 0;

		if (tetrominoShape == TetrominoShapeEnum::O)
		{
			_tetrominoPositionX = 4;
		}
		else
		{
			_tetrominoPositionX = 3;
		}
	}

	bool Board::CanMoveToLeft(std::vector<std::vector<int>> shapeToCheck)
	{
		bool isMovable = true;

		int tetrominoTileX = _tetrominoPositionX - 1;
		int tetrominoTileY = _tetrominoPositionY - 1;

		for (int i = 0; i < shapeToCheck.size(); i++) // Y Axis
		{
			tetrominoTileY++;

			tetrominoTileX = _tetrominoPositionX - 1;
			for (int j = 0; j < shapeToCheck[i].size(); j++) // X Axis
			{
				tetrominoTileX++;
				if (shapeToCheck[i][j] != static_cast<int>(TetrominoColorEnum::NONE))
				{
					// Left collision
					if (tetrominoTileX <= 0 ||
						_logicalTetrominosArray[tetrominoTileY][tetrominoTileX - 1] != TetrominoColorEnum::NONE)
					{
						isMovable = false;
					}

					break; // We only check the first colored tile of the line for left collision
				}
			}
		}

		return isMovable;
	}

	bool Board::CanMoveToRight(std::vector<std::vector<int>> shapeToCheck)
	{
		bool isMovable = true;

		int tetrominoTileX = _tetrominoPositionX - 1;
		int tetrominoTileY = _tetrominoPositionY - 1;

		for (int i = 0; i < shapeToCheck.size(); i++) // Y Axis
		{
			tetrominoTileY++;

			tetrominoTileX = _tetrominoPositionX + shapeToCheck[i].size();
			for (int j = shapeToCheck[i].size() - 1; j >= 0; j--) // X Axis
			{
				tetrominoTileX--;
				if (shapeToCheck[i][j] != static_cast<int>(TetrominoColorEnum::NONE))
				{
					// Right collision
					if (tetrominoTileX >= EntitiesConsts::NB_COLUMNS - 1 ||
						_logicalTetrominosArray[tetrominoTileY][tetrominoTileX + 1] != TetrominoColorEnum::NONE)
					{
						isMovable = false;
					}
					break;
				}
			}
		}

		return isMovable;
	}

	bool Board::CanRotate(std::vector<std::vector<int>> shapeToCheck) const
	{
		bool isRotatable = true;

		int tetrominoTileX = _tetrominoPositionX - 1;
		int tetrominoTileY = _tetrominoPositionY - 1;

		for (int i = 0; i < shapeToCheck.size(); i++) // Y Axis
		{
			tetrominoTileY++;

			tetrominoTileX = _tetrominoPositionX - 1;
			for (int j = 0; j < shapeToCheck[i].size(); j++) // X Axis
			{
				tetrominoTileX++;

				// Left and right collision
				if (shapeToCheck[i][j] != static_cast<int>(TetrominoColorEnum::NONE)
					&& _currentTetromino->GetTetrominoCurrentShape()[i][j] != static_cast<int>(TetrominoColorEnum::NONE))
				{
					if (tetrominoTileX - j < 0 || tetrominoTileX >= EntitiesConsts::NB_COLUMNS - 1)
					{
						isRotatable = false;
					}
				}

				// Bottom collision
				if (shapeToCheck[i][j] != static_cast<int>(TetrominoColorEnum::NONE)
					&& tetrominoTileY >= EntitiesConsts::NB_ROWS)
				{
					isRotatable = false;
				}

				// Others pieces collision
				if (tetrominoTileX > 0 && tetrominoTileX < EntitiesConsts::NB_COLUMNS && tetrominoTileY < EntitiesConsts::NB_ROWS)
				{
					if (_currentTetromino->GetTetrominoCurrentShape()[i][j] == static_cast<int>(TetrominoColorEnum::NONE)
						&& _logicalTetrominosArray[tetrominoTileY][tetrominoTileX] != TetrominoColorEnum::NONE)
					{
						isRotatable = false;
					}
				}
			}
		}

		return isRotatable;
	}

	bool Board::CanRotateLeft() const
	{
		return CanRotate(_currentTetromino->GetPreviousShape());
	}

	bool Board::CanRotateRight() const
	{
		return CanRotate(_currentTetromino->GetNextShape());
	}

	void Board::RemoveFullLines()
	{
		int countLines = _logicalTetrominosArray.size();

		// Searching for full lines
		auto iteratorRemoveFullLines = [](std::vector<TetrominoColorEnum> line) -> bool
		{
			bool needToBeRemoved = true;

			for (auto tile : line)
			{
				if (tile == TetrominoColorEnum::NONE)
					needToBeRemoved = false;
			}

			return needToBeRemoved;
		};

		// Call std::remove_if and obtain iterator
		auto iterator = std::remove_if(_logicalTetrominosArray.begin(), _logicalTetrominosArray.end(), iteratorRemoveFullLines);
		// Delete full lines
		_logicalTetrominosArray.erase(iterator, _logicalTetrominosArray.end());


		// Inserting new empty lines
		int countLinesRemoved = countLines - _logicalTetrominosArray.size();
		_logicalTetrominosArray.insert(_logicalTetrominosArray.begin(), countLinesRemoved, {
			TetrominoColorEnum::NONE,
			TetrominoColorEnum::NONE,
			TetrominoColorEnum::NONE,
			TetrominoColorEnum::NONE,
			TetrominoColorEnum::NONE,
			TetrominoColorEnum::NONE,
			TetrominoColorEnum::NONE,
			TetrominoColorEnum::NONE,
			TetrominoColorEnum::NONE,
			TetrominoColorEnum::NONE
		});

		CheckLevel(countLinesRemoved);
		UpdateScore(countLinesRemoved);

	}

	bool Board::isGameOverInternal()
	{
		auto shapeToCheck = _currentTetromino->GetTetrominoCurrentShape();
		bool isGameOver = false;

		int tetrominoTileX = _tetrominoPositionX - 1;
		int tetrominoTileY = _tetrominoPositionY - 1;

		for (int i = 0; i < shapeToCheck.size(); i++) // Y Axis
		{
			tetrominoTileY++;

			tetrominoTileX = _tetrominoPositionX - 1;
			for (int j = 0; j < shapeToCheck[i].size(); j++) // X Axis
			{
				tetrominoTileX++;

				if(shapeToCheck[i][j] != static_cast<int>(TetrominoColorEnum::NONE)
					&& _logicalTetrominosArray[tetrominoTileY + 1][tetrominoTileX] != TetrominoColorEnum::NONE)
				{
					_scoreComponent->SaveScoreIfBest();
					isGameOver = true;
					break;
				}
			}
		}

		return isGameOver;
	}

	bool Board::IsCollideBottom()
	{
		auto shapeToCheck = _currentTetromino->GetTetrominoCurrentShape();
		bool isCollide = false;

		int tetrominoTileX = _tetrominoPositionX - 1;
		int tetrominoTileY = _tetrominoPositionY - 1;

		for (int i = 0; i < shapeToCheck.size(); i++) // Y Axis
		{
			tetrominoTileY++;

			tetrominoTileX = _tetrominoPositionX - 1;
			for (int j = 0; j < shapeToCheck[i].size(); j++) // X Axis
			{
				tetrominoTileX++;

				// Bottom collision
				if (shapeToCheck[i][j] != static_cast<int>(TetrominoColorEnum::NONE)
					&& tetrominoTileY + 1 >= EntitiesConsts::NB_ROWS)
				{
					isCollide = true;
				}
				else // Others pieces bottom collision
				{
					// Si tuile du tétromino est pleine
					if (shapeToCheck[i][j] != static_cast<int>(TetrominoColorEnum::NONE))
					{

						// Si pas de tuile de tétromino en dessous et tuile du plateau est pleine
						if (i == shapeToCheck.size() - 1
							&& _logicalTetrominosArray[tetrominoTileY + 1][tetrominoTileX] != TetrominoColorEnum::NONE)
						{
							// Alors isCollide = true;
							isCollide = true;
							// Fin Si
						}
						else if (i < shapeToCheck.size() - 1)
						{
							// Si tuile du tétromino en dessous est vide et tuile du plateau est pleine
							if (shapeToCheck[i + 1][j] == static_cast<int>(TetrominoColorEnum::NONE)
								&& _logicalTetrominosArray[tetrominoTileY + 1][tetrominoTileX] != TetrominoColorEnum::NONE)
							{
								// Alors isCollide = true;
								isCollide = true;
								// Fin Si
							}
						}

						// Fin Si
					}
				}

			}
		}

		return isCollide;
	}

	void Board::SetTimers()
	{
		_moveTetrominoToLeftOrRightTimer.SetInputRepeatFrequency(150);
		_moveTetrominoToLeftOrRightTimer.SetStartHoldInputDownDelay(500);
		_moveTetrominoToLeftOrRightTimer.SetDelay(200);

		_tetrominoMovingDownTimer.SetRepeatFrequency(MOVE_DOWN_TIMER_DEFAULT_FREQUENCY);
	}

	void Board::CheckLevel(int nbLinesJustRemoved)
	{
		if (nbLinesJustRemoved > 0)
		{
			_linesRemovedCounterComponent->AddNumberOfLinesRemovedToCounter(nbLinesJustRemoved);
			_levelComponent->DefineLevel(_linesRemovedCounterComponent->GetLinesRemovedCounter());

			_moveDownTimerFrequency = MOVE_DOWN_TIMER_DEFAULT_FREQUENCY - ((_levelComponent->GetLevel() - 1) * 100);
			_tetrominoMovingDownTimer.SetRepeatFrequency(_moveDownTimerFrequency);
		}
	}

	void Board::UpdateScore(int nbLinesJustRemoved)
	{
		if (nbLinesJustRemoved > 0)
		{
			_scoreComponent->UpdateScore(_levelComponent->GetLevel(), nbLinesJustRemoved);
		}
		else
		{
			_scoreComponent->UpdateScore(_levelComponent->GetLevel());
		}
	}
}
