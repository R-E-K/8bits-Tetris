#include "Board.h"
#include "ImageLoader.h"

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
	}


	Board::~Board()
	{
	}

	void Board::Draw()
	{
		DrawBorder();
		DrawBackground();
		DrawTetrominos();
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

	std::shared_ptr<SDL_Texture> Board::GetTetrominoTexture(std::string const& imageFilePath)
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
}
