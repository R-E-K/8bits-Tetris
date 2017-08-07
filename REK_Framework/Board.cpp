#include "Board.h"
#include "ImageLoader.h"
#include <algorithm>


namespace REKFramework
{
	Board::Board()
	{
		// It will be a square
		backgroundTextureWidth = (SCREEN_HEIGHT * (85.0 / 100.0)) / EntitiesConsts::NB_ROWS;
		backgroundTextureHeight = (SCREEN_HEIGHT * (85.0 / 100.0)) / EntitiesConsts::NB_ROWS;

		gameOver = false;
		MoveDownTimerFrequency = MoveDownTimerDefaultFrequency;

		SetBorderBackground();
		SetTexturesBackground();
		SetTetrominosTextures();
		InitLogicalTetrominosArray();
		SetTimers();

		TetrominoShapeEnum selectedShape = RandomlySelectTetrominoType();
		CurrentTetromino = std::make_unique<Tetromino>(selectedShape);
		SetTetrominoStartPosition(selectedShape);
		MoveTetrominoToLeftOrRightTimer.SetDelay(200);
		TetrominoMovingDownTimer.SetDelay(200);

		_nextTetrominoComponent = std::make_unique<NextTetrominoComponent>(RandomlySelectTetrominoType());
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

		_levelComponent.Draw();
		_linesRemovedCounterComponent.Draw();
		_scoreAndNextTetrominoComponent.Draw();
		_nextTetrominoComponent->Draw();
	}

	void Board::NewTetromino()
	{
		CurrentTetromino = _nextTetrominoComponent->PopTetromino();
		_nextTetrominoComponent->SetTetromino(RandomlySelectTetrominoType());
		SetTetrominoStartPosition(CurrentTetromino->GetShape());

		MoveTetrominoToLeftOrRightTimer.SetDelay(200);
		TetrominoMovingDownTimer.SetDelay(200);
		CurrentTetromino->SetRotateTimerDelay(200);

		if (isGameOverInternal())
		{
			gameOver = true;
		}
	}

	void Board::Update()
	{

		// Need to be draw here to have the last shape
		DrawCurrentTetrominosOnBoard();

		TetrominoMovingDownTimer.Execute([&]()
		{
			if (!IsCollideBottom())
			{
				TetrominoPositionY++;
			}
			else
			{
				// Clear Stacks
				// Unfortunately, extension methods don't exist in C++
				while (!TetrominoTileXPrevious.empty())
				{
					TetrominoTileXPrevious.pop();
				}

				while (!TetrominoTileYPrevious.empty())
				{
					TetrominoTileYPrevious.pop();
				}

				RemoveFullLines();

				NewTetromino();
			}
		});
	}

	bool Board::IsGameOver() const
	{
		return gameOver;
	}

	void Board::MoveTetrominoToTheLeft()
	{
		if (CanMoveToLeft(CurrentTetromino->GetTetrominoCurrentShape()))
		{
			MoveTetrominoToLeftOrRightTimer.Execute([&]()
			{
				TetrominoPositionX--;
			});
		}
	}

	void Board::MoveTetrominoToTheRight()
	{
		if (CanMoveToRight(CurrentTetromino->GetTetrominoCurrentShape()))
		{
			MoveTetrominoToLeftOrRightTimer.Execute([&]()
			{
				TetrominoPositionX++;
			});
		}
	}

	void Board::RotateTetrominoToLeftIfPossible()
	{
		if (CanRotateLeft())
		{
			CurrentTetromino->RotateLeft();
		}
	}

	void Board::RotateTetrominoToRightIfPossible()
	{
		if (CanRotateRight())
		{
			CurrentTetromino->RotateRight();
		}
	}

	void Board::MoveTetrominoDown()
	{
		TetrominoMovingDownTimer.SetRepeatFrequency(50);
	}

	void Board::MoveTetrominoDownRelease()
	{
		TetrominoMovingDownTimer.SetRepeatFrequency(MoveDownTimerFrequency);
	}

	void Board::SetTexturesBackground()
	{
		auto surfaceLight = std::unique_ptr<SDL_Surface, SdlDeleter>(
			SDL_CreateRGBSurface(0, backgroundTextureWidth, backgroundTextureHeight, 32, 0, 0, 0, 0)
			, SdlDeleter());

		SDL_FillRect(surfaceLight.get(), nullptr, SDL_MapRGB(surfaceLight->format, 215, 215, 215));

		lightBackgroundTexture = std::shared_ptr<SDL_Texture>(
			SDL_CreateTextureFromSurface(SDLMainObjectsProvider::GetRendererRawPointer(), surfaceLight.get()),
			SdlDeleter()
			);


		auto darkLight = std::unique_ptr<SDL_Surface, SdlDeleter>(
			SDL_CreateRGBSurface(0, backgroundTextureWidth, backgroundTextureHeight, 32, 0, 0, 0, 0)
			, SdlDeleter());

		SDL_FillRect(darkLight.get(), nullptr, SDL_MapRGB(darkLight->format, 171, 171, 171));

		darkBackgroundTexture = std::shared_ptr<SDL_Texture>(
			SDL_CreateTextureFromSurface(SDLMainObjectsProvider::GetRendererRawPointer(), darkLight.get()),
			SdlDeleter()
			);
	}

	void Board::SetBorderBackground()
	{
		auto surfaceBorder = std::unique_ptr<SDL_Surface, SdlDeleter>(
			SDL_CreateRGBSurface(0, backgroundTextureWidth * EntitiesConsts::NB_COLUMNS, backgroundTextureHeight * EntitiesConsts::NB_ROWS, 32, 0, 0, 0, 0)
			, SdlDeleter());

		SDL_FillRect(surfaceBorder.get(), nullptr, SDL_MapRGB(surfaceBorder->format, 0, 0, 0));

		borderBackgroundTexture = std::unique_ptr<SDL_Texture, SdlDeleter>(
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
		TetrominosTextures.resize(7);
		TetrominosTextures[0] = GetTetrominoTexture("resources/graphics/tetrominos/blue.png");
		TetrominosTextures[1] = GetTetrominoTexture("resources/graphics/tetrominos/brown.png");
		TetrominosTextures[2] = GetTetrominoTexture("resources/graphics/tetrominos/green.png");
		TetrominosTextures[3] = GetTetrominoTexture("resources/graphics/tetrominos/orange.png");
		TetrominosTextures[4] = GetTetrominoTexture("resources/graphics/tetrominos/purple.png");
		TetrominosTextures[5] = GetTetrominoTexture("resources/graphics/tetrominos/red.png");
		TetrominosTextures[6] = GetTetrominoTexture("resources/graphics/tetrominos/yellow.png");
	}

	void Board::InitLogicalTetrominosArray()
	{
		// Set up sizes. (HEIGHT x WIDTH)
		logicalTetrominosArray.resize(EntitiesConsts::NB_ROWS);
		for (int i = 0; i < EntitiesConsts::NB_ROWS; ++i)
			logicalTetrominosArray[i].resize(EntitiesConsts::NB_COLUMNS);

		for (int i = 0; i < EntitiesConsts::NB_ROWS; i++)
		{
			for (int j = 0; j < EntitiesConsts::NB_COLUMNS; j++)
			{
				logicalTetrominosArray[i][j] = TetrominoColorEnum::NONE;
			}
		}
	}

	void Board::DrawCurrentTetrominosOnBoard()
	{
		if (!TetrominoTileXPrevious.empty())
		{
			for (int i = 0; i < TetrominoTileYPrevious.size(); i++) // Y Axis
			{
				int x = TetrominoTileXPrevious.top();
				TetrominoTileXPrevious.pop();

				int y = TetrominoTileYPrevious.top();
				TetrominoTileYPrevious.pop();

				logicalTetrominosArray[y][x] = TetrominoColorEnum::NONE;
			}
		}

		auto Tetromino = CurrentTetromino->GetTetrominoCurrentShape();

		int tetrominoTileX = TetrominoPositionX - 1;
		int tetrominoTileY = TetrominoPositionY - 1;

		for (int i = 0; i < Tetromino.size(); i++) // Y Axis
		{
			tetrominoTileY++;

			tetrominoTileX = TetrominoPositionX - 1;
			for (int j = 0; j < Tetromino[i].size(); j++) // X Axis
			{
				tetrominoTileX++;

				if (Tetromino[i][j] != static_cast<int>(TetrominoColorEnum::NONE))
				{
					logicalTetrominosArray[tetrominoTileY][tetrominoTileX] = CurrentTetromino->GetColor();
					TetrominoTileYPrevious.push(tetrominoTileY);
					TetrominoTileXPrevious.push(tetrominoTileX);
				}
			}
		}
	}

	void Board::DrawBorder() const
	{
		SDL_Rect backgroundTilePosition;
		backgroundTilePosition.x = (SCREEN_WIDTH / 2) - ((backgroundTextureWidth * EntitiesConsts::NB_COLUMNS) / 2) + backgroundTextureWidth - EntitiesConsts::BORDER_THICKNESS;
		backgroundTilePosition.y = SCREEN_HEIGHT * (12.0 / 100.0) - EntitiesConsts::BORDER_THICKNESS; // Start at 10% from top
		backgroundTilePosition.w = (backgroundTextureWidth * EntitiesConsts::NB_COLUMNS) + (EntitiesConsts::BORDER_THICKNESS * 2);
		backgroundTilePosition.h = (backgroundTextureHeight * EntitiesConsts::NB_ROWS) + (EntitiesConsts::BORDER_THICKNESS * 2);

		SDL_RenderCopy(SDLMainObjectsProvider::GetRendererRawPointer()
			, borderBackgroundTexture.get()
			, nullptr, &backgroundTilePosition);
	}

	void Board::DrawBackground() const
	{
		int backgroundTileXInitPosition = (SCREEN_WIDTH / 2) - ((backgroundTextureWidth * EntitiesConsts::NB_COLUMNS) / 2);

		SDL_Rect backgroundTilePosition;
		backgroundTilePosition.x = backgroundTileXInitPosition - backgroundTextureWidth;
		backgroundTilePosition.y = SCREEN_HEIGHT * (12.0 / 100.0) - backgroundTextureHeight; // Start at 10% from top
		backgroundTilePosition.w = backgroundTextureWidth;
		backgroundTilePosition.h = backgroundTextureHeight;

		bool isLight;

		for (int i = 0; i < EntitiesConsts::NB_ROWS; i++)
		{
			backgroundTilePosition.y += backgroundTextureHeight;
			backgroundTilePosition.x = backgroundTileXInitPosition;

			// First column is always light
			isLight = true;
			for (int j = 0; j < EntitiesConsts::NB_COLUMNS; j++)
			{
				backgroundTilePosition.x += backgroundTextureWidth;

				SDL_RenderCopy(SDLMainObjectsProvider::GetRendererRawPointer()
					, isLight ? lightBackgroundTexture.get() : darkBackgroundTexture.get()
					, nullptr, &backgroundTilePosition);

				isLight = !isLight;
			}
		}
	}

	void Board::DrawTetrominos() const
	{
		int backgroundTileXInitPosition = (SCREEN_WIDTH / 2) - ((backgroundTextureWidth * EntitiesConsts::NB_COLUMNS) / 2);

		SDL_Rect backgroundTilePosition;
		backgroundTilePosition.x = backgroundTileXInitPosition - backgroundTextureWidth;
		backgroundTilePosition.y = SCREEN_HEIGHT * (12.0 / 100.0) - backgroundTextureHeight; // Start at 10% from top
		backgroundTilePosition.w = backgroundTextureWidth;
		backgroundTilePosition.h = backgroundTextureHeight;

		for (int i = 0; i < EntitiesConsts::NB_ROWS; i++)
		{
			backgroundTilePosition.y += backgroundTextureHeight;
			backgroundTilePosition.x = backgroundTileXInitPosition;

			for (int j = 0; j < EntitiesConsts::NB_COLUMNS; j++)
			{
				backgroundTilePosition.x += backgroundTextureWidth;

				if (logicalTetrominosArray[i][j] != TetrominoColorEnum::NONE)
				{
					SDL_RenderCopy(SDLMainObjectsProvider::GetRendererRawPointer()
						, TetrominosTextures[static_cast<int>(logicalTetrominosArray[i][j])].get()
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
		TetrominoPositionY = 0;

		if (tetrominoShape == TetrominoShapeEnum::O)
		{
			TetrominoPositionX = 4;
		}
		else
		{
			TetrominoPositionX = 3;
		}
	}

	bool Board::CanMoveToLeft(std::vector<std::vector<int>> shapeToCheck)
	{
		bool isMovable = true;

		int tetrominoTileX = TetrominoPositionX - 1;
		int tetrominoTileY = TetrominoPositionY - 1;

		for (int i = 0; i < shapeToCheck.size(); i++) // Y Axis
		{
			tetrominoTileY++;

			tetrominoTileX = TetrominoPositionX - 1;
			for (int j = 0; j < shapeToCheck[i].size(); j++) // X Axis
			{
				tetrominoTileX++;
				if (shapeToCheck[i][j] != static_cast<int>(TetrominoColorEnum::NONE))
				{
					// Left collision
					if (tetrominoTileX <= 0 ||
						logicalTetrominosArray[tetrominoTileY][tetrominoTileX - 1] != TetrominoColorEnum::NONE)
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

		int tetrominoTileX = TetrominoPositionX - 1;
		int tetrominoTileY = TetrominoPositionY - 1;

		for (int i = 0; i < shapeToCheck.size(); i++) // Y Axis
		{
			tetrominoTileY++;

			tetrominoTileX = TetrominoPositionX + shapeToCheck[i].size();
			for (int j = shapeToCheck[i].size() - 1; j >= 0; j--) // X Axis
			{
				tetrominoTileX--;
				if (shapeToCheck[i][j] != static_cast<int>(TetrominoColorEnum::NONE))
				{
					// Right collision
					if (tetrominoTileX >= EntitiesConsts::NB_COLUMNS - 1 ||
						logicalTetrominosArray[tetrominoTileY][tetrominoTileX + 1] != TetrominoColorEnum::NONE)
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

		int tetrominoTileX = TetrominoPositionX - 1;
		int tetrominoTileY = TetrominoPositionY - 1;

		for (int i = 0; i < shapeToCheck.size(); i++) // Y Axis
		{
			tetrominoTileY++;

			tetrominoTileX = TetrominoPositionX - 1;
			for (int j = 0; j < shapeToCheck[i].size(); j++) // X Axis
			{
				tetrominoTileX++;

				// Left and right collision
				if (shapeToCheck[i][j] != static_cast<int>(TetrominoColorEnum::NONE)
					&& CurrentTetromino->GetTetrominoCurrentShape()[i][j] != static_cast<int>(TetrominoColorEnum::NONE))
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
					if (CurrentTetromino->GetTetrominoCurrentShape()[i][j] == static_cast<int>(TetrominoColorEnum::NONE)
						&& logicalTetrominosArray[tetrominoTileY][tetrominoTileX] != TetrominoColorEnum::NONE)
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
		return CanRotate(CurrentTetromino->GetPreviousShape());
	}

	bool Board::CanRotateRight() const
	{
		return CanRotate(CurrentTetromino->GetNextShape());
	}

	void Board::RemoveFullLines()
	{
		int countLines = logicalTetrominosArray.size();

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
		auto iterator = std::remove_if(logicalTetrominosArray.begin(), logicalTetrominosArray.end(), iteratorRemoveFullLines);
		// Delete full lines
		logicalTetrominosArray.erase(iterator, logicalTetrominosArray.end());


		// Inserting new empty lines
		int countLinesRemoved = countLines - logicalTetrominosArray.size();
		logicalTetrominosArray.insert(logicalTetrominosArray.begin(), countLinesRemoved, {
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
		auto shapeToCheck = CurrentTetromino->GetTetrominoCurrentShape();
		bool isGameOver = false;

		int tetrominoTileX = TetrominoPositionX - 1;
		int tetrominoTileY = TetrominoPositionY - 1;

		for (int i = 0; i < shapeToCheck.size(); i++) // Y Axis
		{
			tetrominoTileY++;

			tetrominoTileX = TetrominoPositionX - 1;
			for (int j = 0; j < shapeToCheck[i].size(); j++) // X Axis
			{
				tetrominoTileX++;

				if(shapeToCheck[i][j] != static_cast<int>(TetrominoColorEnum::NONE)
					&& logicalTetrominosArray[tetrominoTileY + 1][tetrominoTileX] != TetrominoColorEnum::NONE)
				{
					isGameOver = true;
					break;
				}
			}
		}

		return isGameOver;
	}

	bool Board::IsCollideBottom()
	{
		auto shapeToCheck = CurrentTetromino->GetTetrominoCurrentShape();
		bool isCollide = false;

		int tetrominoTileX = TetrominoPositionX - 1;
		int tetrominoTileY = TetrominoPositionY - 1;

		for (int i = 0; i < shapeToCheck.size(); i++) // Y Axis
		{
			tetrominoTileY++;

			tetrominoTileX = TetrominoPositionX - 1;
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
							&& logicalTetrominosArray[tetrominoTileY + 1][tetrominoTileX] != TetrominoColorEnum::NONE)
						{
							// Alors isCollide = true;
							isCollide = true;
							// Fin Si
						}
						else if (i < shapeToCheck.size() - 1)
						{
							// Si tuile du tétromino en dessous est vide et tuile du plateau est pleine
							if (shapeToCheck[i + 1][j] == static_cast<int>(TetrominoColorEnum::NONE)
								&& logicalTetrominosArray[tetrominoTileY + 1][tetrominoTileX] != TetrominoColorEnum::NONE)
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
		MoveTetrominoToLeftOrRightTimer.SetInputRepeatFrequency(150);
		MoveTetrominoToLeftOrRightTimer.SetStartHoldInputDownDelay(500);
		MoveTetrominoToLeftOrRightTimer.SetDelay(200);

		TetrominoMovingDownTimer.SetRepeatFrequency(MoveDownTimerDefaultFrequency);
	}

	void Board::CheckLevel(int nbLinesJustRemoved)
	{
		if (nbLinesJustRemoved > 0)
		{
			_linesRemovedCounterComponent.AddNumberOfLinesRemovedToCounter(nbLinesJustRemoved);
			_levelComponent.DefineLevel(_linesRemovedCounterComponent.GetLinesRemovedCounter());

			MoveDownTimerFrequency = MoveDownTimerDefaultFrequency - ((_levelComponent.GetLevel() - 1) * 100);
			TetrominoMovingDownTimer.SetRepeatFrequency(MoveDownTimerFrequency);
		}
	}

	void Board::UpdateScore(int nbLinesJustRemoved)
	{
		if (nbLinesJustRemoved > 0)
		{
			_scoreAndNextTetrominoComponent.UpdateScore(_levelComponent.GetLevel(), nbLinesJustRemoved);
		}
		else
		{
			_scoreAndNextTetrominoComponent.UpdateScore(_levelComponent.GetLevel());
		}
	}
}
