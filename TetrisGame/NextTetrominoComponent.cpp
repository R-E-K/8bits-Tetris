#include "NextTetrominoComponent.h"
#include "ImageLoader.h"

namespace REKFramework
{
	NextTetrominoComponent::NextTetrominoComponent(TetrominoShapeEnum tetrominoShapeEnum)
	{
		_backgroundTextureWidth = (SCREEN_HEIGHT * (20.0 / 100.0));
		_backgroundTextureHeight = (SCREEN_HEIGHT * (20.0 / 100.0));

		LoadTextures();

		_nextTetromino = std::make_unique<Tetromino>(tetrominoShapeEnum);
	}

	NextTetrominoComponent::~NextTetrominoComponent()
	{
	}

	void NextTetrominoComponent::Draw() const
	{
		DrawBorder();
		DrawBackground();
		DrawTitle();
		DrawNextTetromino();
	}

	void NextTetrominoComponent::SetTetromino(TetrominoShapeEnum tetrominoShapeEnum)
	{
		_nextTetromino = std::make_unique<Tetromino>(tetrominoShapeEnum);
	}

	std::unique_ptr<Tetromino> NextTetrominoComponent::PopTetromino()
	{
		return std::move(_nextTetromino);
	}

	std::shared_ptr<SDL_Texture> NextTetrominoComponent::GetTetrominoTexture(std::string const& imageFilePath) const
	{
		auto tetrominoSurface = ImageLoader::GetImageWithoutTransparency(imageFilePath);

		return std::shared_ptr<SDL_Texture>(
			SDL_CreateTextureFromSurface(SDLMainObjectsProvider::GetRendererRawPointer(), tetrominoSurface.get()),
			SdlDeleter()
			);
	}

	void NextTetrominoComponent::LoadTextures()
	{
		auto darkLight = std::unique_ptr<SDL_Surface, SdlDeleter>(
			SDL_CreateRGBSurface(0, _backgroundTextureWidth, _backgroundTextureHeight, 32, 0, 0, 0, 0)
			, SdlDeleter());

		SDL_FillRect(darkLight.get(), nullptr, SDL_MapRGB(darkLight->format, 171, 171, 171));

		_backgroundTexture = std::unique_ptr<SDL_Texture, SdlDeleter>(
			SDL_CreateTextureFromSurface(SDLMainObjectsProvider::GetRendererRawPointer(), darkLight.get()),
			SdlDeleter()
			);

		auto surfaceBorder = std::unique_ptr<SDL_Surface, SdlDeleter>(
			SDL_CreateRGBSurface(0, _backgroundTextureWidth * EntitiesConsts::NB_COLUMNS, _backgroundTextureHeight, 32, 0, 0, 0, 0)
			, SdlDeleter());

		SDL_FillRect(surfaceBorder.get(), nullptr, SDL_MapRGB(surfaceBorder->format, 0, 0, 0));

		_borderBackgroundTexture = std::unique_ptr<SDL_Texture, SdlDeleter>(
			SDL_CreateTextureFromSurface(SDLMainObjectsProvider::GetRendererRawPointer(), surfaceBorder.get()),
			SdlDeleter()
			);

		TetrominosTextures.resize(7);
		TetrominosTextures[0] = GetTetrominoTexture("resources/graphics/tetrominos/blue.png");
		TetrominosTextures[1] = GetTetrominoTexture("resources/graphics/tetrominos/brown.png");
		TetrominosTextures[2] = GetTetrominoTexture("resources/graphics/tetrominos/green.png");
		TetrominosTextures[3] = GetTetrominoTexture("resources/graphics/tetrominos/orange.png");
		TetrominosTextures[4] = GetTetrominoTexture("resources/graphics/tetrominos/purple.png");
		TetrominosTextures[5] = GetTetrominoTexture("resources/graphics/tetrominos/red.png");
		TetrominosTextures[6] = GetTetrominoTexture("resources/graphics/tetrominos/yellow.png");
	}

	void NextTetrominoComponent::DrawBorder() const
	{
		SDL_Rect backgroundTilePosition;
		backgroundTilePosition.x = (SCREEN_WIDTH / 2) + (SCREEN_WIDTH / 4) - EntitiesConsts::BORDER_THICKNESS;
		backgroundTilePosition.y = SCREEN_HEIGHT * (2.0 / 100.0) - EntitiesConsts::BORDER_THICKNESS; // Start at 2% from top
		backgroundTilePosition.w = _backgroundTextureWidth + (EntitiesConsts::BORDER_THICKNESS * 2);
		backgroundTilePosition.h = _backgroundTextureHeight + (EntitiesConsts::BORDER_THICKNESS * 2);

		SDL_RenderCopy(SDLMainObjectsProvider::GetRendererRawPointer()
			, _borderBackgroundTexture.get()
			, nullptr, &backgroundTilePosition);
	}

	void NextTetrominoComponent::DrawBackground() const
	{
		SDL_Rect backgroundTilePosition;
		backgroundTilePosition.x = (SCREEN_WIDTH / 2) + (SCREEN_WIDTH / 4);
		backgroundTilePosition.y = SCREEN_HEIGHT * (2.0 / 100.0);
		backgroundTilePosition.w = _backgroundTextureWidth;
		backgroundTilePosition.h = _backgroundTextureHeight;

		SDL_RenderCopy(SDLMainObjectsProvider::GetRendererRawPointer()
			, _backgroundTexture.get()
			, nullptr, &backgroundTilePosition);
	}

	void NextTetrominoComponent::DrawTitle() const
	{
		SDL_Color color = { 255, 255, 255 };

		DrawTextService::DrawTextWithSizeAndColor("Next"
			, (SCREEN_WIDTH / 2) + (SCREEN_WIDTH / 4) + (_backgroundTextureWidth * (5.0 / 100.0))
			, SCREEN_HEIGHT * (2.0 / 100.0) + (_backgroundTextureHeight * (5.0 / 100.0))
			, _backgroundTextureHeight * (25.0 / 100.0)
			, color);
	}

	void NextTetrominoComponent::DrawNextTetromino() const
	{
		SDL_Color color = { 50, 50, 255 };
		bool isEmptyLine = true;

		auto Tetromino = _nextTetromino->GetTetrominoCurrentShape();

		SDL_Rect backgroundTilePosition;

		int initTetrominoTileX = (SCREEN_WIDTH / 2) + (SCREEN_WIDTH / 4) + (_backgroundTextureWidth * (10.0 / 100.0)) - _backgroundTextureHeight / 5;
		backgroundTilePosition.x = initTetrominoTileX;
		backgroundTilePosition.y = SCREEN_HEIGHT * (2.0 / 100.0) + (_backgroundTextureHeight * (20.0 / 100.0));
		backgroundTilePosition.w = _backgroundTextureHeight / 5;
		backgroundTilePosition.h = _backgroundTextureHeight / 5;

		for (int i = 0; i < Tetromino.size(); i++) // Y Axis
		{
			if (i > 0 && isEmptyLine)
			{
				backgroundTilePosition.y -= _backgroundTextureHeight / 5;
				isEmptyLine = false;
			}

			backgroundTilePosition.y += _backgroundTextureHeight / 5;


			backgroundTilePosition.x = initTetrominoTileX;
			for (int j = 0; j < Tetromino[i].size(); j++) // X Axis
			{
				backgroundTilePosition.x += _backgroundTextureHeight / 5;

				if (Tetromino[i][j] != static_cast<int>(TetrominoColorEnum::NONE))
				{
					SDL_RenderCopy(SDLMainObjectsProvider::GetRendererRawPointer()
						, TetrominosTextures[static_cast<int>(_nextTetromino->GetColor())].get()
						, nullptr, &backgroundTilePosition);

					isEmptyLine = false;
				}
			}
		}
	}
}
