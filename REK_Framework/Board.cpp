#include "Board.h"
#include "ImageLoader.h"
#include <ctime>

namespace REKFramework
{
	Board::Board()
	{
		// It will be a square
		backgroundTextureWidth = (SCREEN_HEIGHT * (85.0 / 100.0)) / NB_ROWS;
		backgroundTextureHeight = (SCREEN_HEIGHT * (85.0 / 100.0)) / NB_ROWS;

		SetBorderBackground();
		SetTexturesBackground();
		SetTetrominosTextures();
		InitLogicalTetrominosArray();

		NewTetromino();
	}


	Board::~Board()
	{
	}

	void Board::Draw() const
	{
		DrawBorder();
		DrawBackground();
		DrawTetrominos();
	}

	void Board::NewTetromino()
	{
		TetrominoShapeEnum selectedShape = RandomlySelectTetrominoType();
		CurrentTetromino = std::make_unique<Tetromino>(selectedShape);
		SetTetrominoStartPosition(selectedShape);
	}

	void Board::Update()
	{
		PlaceCurrentTetrominosOnBoard();
		moveLeftTime = SDL_GetTicks();
		moveRightTime = SDL_GetTicks();
	}

	void Board::MoveTetrominoToTheLeft()
	{
		IsHoldInputMoveLeft = (moveLeftTime - moveLeftLastTime <= 30);

		if(IsHoldInputMoveLeft)
		{
			if (!IsJustHoldMoveLeft)
			{
				if (moveLeftTime - moveLeftHoldTime >= 150)
				{
					TetrominoPositionX--;
					moveLeftHoldTime = moveLeftTime;
				}
			}
			else
			{
				IsJustHoldMoveLeft = false;
				moveLeftHoldTime = moveLeftTime + 500; // Temporisation de 500 ms sur le maintient de la touche
			}
		}
		else if (!IsHoldInputMoveLeft)
		{
			if (moveLeftTime - moveLeftLastTime >= 50)
			{
				TetrominoPositionX--;
				IsJustHoldMoveLeft = true;
			}
			moveLeftLastTime = moveLeftTime;
		}
	}

	void Board::MoveTetrominoToTheRight()
	{
		IsHoldInputMoveRight = (moveRightTime - moveRightLastTime <= 30);

		if (IsHoldInputMoveRight)
		{
			if (!IsJustHoldMoveRight)
			{
				if (moveRightTime - moveRightHoldTime >= 150)
				{
					TetrominoPositionX++;
					moveRightHoldTime = moveRightTime;
				}
			}
			else
			{
				IsJustHoldMoveRight = false;
				moveRightHoldTime = moveRightTime + 500; // Temporisation de 500 ms sur le maintient de la touche
			}
			
		}
		else if (!IsHoldInputMoveRight)
		{
			if (moveRightTime - moveRightLastTime >= 50)
			{
				TetrominoPositionX++;
				IsJustHoldMoveRight = true;
			}
			moveRightLastTime = moveRightTime;
		}
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
			SDL_CreateRGBSurface(0, backgroundTextureWidth * NB_COLUMNS, backgroundTextureHeight * NB_ROWS, 32, 0, 0, 0, 0)
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
		logicalTetrominosArray.resize(NB_ROWS);
		for (int i = 0; i < NB_ROWS; ++i)
			logicalTetrominosArray[i].resize(NB_COLUMNS);

		for (int i = 0; i < NB_ROWS; i++)
		{
			for (int j = 0; j < NB_COLUMNS; j++)
			{
				logicalTetrominosArray[i][j] = TetrominoColorEnum::NONE;
			}
		}

		// TESTS
		logicalTetrominosArray[5][2] = TetrominoColorEnum::BLUE;
		logicalTetrominosArray[5][3] = TetrominoColorEnum::BLUE;
		logicalTetrominosArray[5][4] = TetrominoColorEnum::BLUE;
		logicalTetrominosArray[5][5] = TetrominoColorEnum::RED;

		logicalTetrominosArray[6][2] = TetrominoColorEnum::GREEN;
		logicalTetrominosArray[7][2] = TetrominoColorEnum::GREEN;
		logicalTetrominosArray[8][2] = TetrominoColorEnum::GREEN;
		logicalTetrominosArray[9][2] = TetrominoColorEnum::GREEN;

		logicalTetrominosArray[15][2] = TetrominoColorEnum::ORANGE;
		logicalTetrominosArray[15][3] = TetrominoColorEnum::ORANGE;
		logicalTetrominosArray[16][3] = TetrominoColorEnum::ORANGE;
		logicalTetrominosArray[16][4] = TetrominoColorEnum::ORANGE;

		logicalTetrominosArray[17][0] = TetrominoColorEnum::YELLOW;
		logicalTetrominosArray[17][1] = TetrominoColorEnum::BROWN;
		logicalTetrominosArray[17][2] = TetrominoColorEnum::PURPLE;
		logicalTetrominosArray[17][3] = TetrominoColorEnum::RED;
	}

	void Board::PlaceCurrentTetrominosOnBoard()
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

		auto Tetromino = CurrentTetromino->GetTetromino();

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
		backgroundTilePosition.x = (SCREEN_WIDTH / 2) - ((backgroundTextureWidth * NB_COLUMNS) / 2) + backgroundTextureWidth - BORDER_THICKNESS;
		backgroundTilePosition.y = SCREEN_HEIGHT * (12.0 / 100.0) - BORDER_THICKNESS; // Start at 10% from top
		backgroundTilePosition.w = (backgroundTextureWidth * NB_COLUMNS) + (BORDER_THICKNESS * 2);
		backgroundTilePosition.h = (backgroundTextureHeight * NB_ROWS) + (BORDER_THICKNESS * 2);

		SDL_RenderCopy(SDLMainObjectsProvider::GetRendererRawPointer()
			, borderBackgroundTexture.get()
			, nullptr, &backgroundTilePosition);
	}

	void Board::DrawBackground() const
	{
		int backgroundTileXInitPosition = (SCREEN_WIDTH / 2) - ((backgroundTextureWidth * NB_COLUMNS) / 2);

		SDL_Rect backgroundTilePosition;
		backgroundTilePosition.x = backgroundTileXInitPosition - backgroundTextureWidth;
		backgroundTilePosition.y = SCREEN_HEIGHT * (12.0 / 100.0) - backgroundTextureHeight; // Start at 10% from top
		backgroundTilePosition.w = backgroundTextureWidth;
		backgroundTilePosition.h = backgroundTextureHeight;

		bool isLight;

		for (int i = 0; i < NB_ROWS; i++)
		{
			backgroundTilePosition.y += backgroundTextureHeight;
			backgroundTilePosition.x = backgroundTileXInitPosition;

			// First column is always light
			isLight = true;
			for (int j = 0; j < NB_COLUMNS; j++)
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
		int backgroundTileXInitPosition = (SCREEN_WIDTH / 2) - ((backgroundTextureWidth * NB_COLUMNS) / 2);

		SDL_Rect backgroundTilePosition;
		backgroundTilePosition.x = backgroundTileXInitPosition - backgroundTextureWidth;
		backgroundTilePosition.y = SCREEN_HEIGHT * (12.0 / 100.0) - backgroundTextureHeight; // Start at 10% from top
		backgroundTilePosition.w = backgroundTextureWidth;
		backgroundTilePosition.h = backgroundTextureHeight;

		for (int i = 0; i < NB_ROWS; i++)
		{
			backgroundTilePosition.y += backgroundTextureHeight;
			backgroundTilePosition.x = backgroundTileXInitPosition;

			for (int j = 0; j < NB_COLUMNS; j++)
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

		if (rng < 5)
			return TetrominoShapeEnum::I;
		else if (rng < 20)
			return TetrominoShapeEnum::J;
		else if (rng < 35)
			return TetrominoShapeEnum::L;
		else if (rng < 50)
			return TetrominoShapeEnum::O;
		else if (rng < 65)
			return TetrominoShapeEnum::S;
		else if (rng < 80)
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
}
