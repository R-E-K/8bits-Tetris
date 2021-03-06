#include "NextTetrominoComponent.h"

namespace REKTetrisGame
{
	NextTetrominoComponent::NextTetrominoComponent(double widthPercent, double HeightPercent, TetrominoShapeEnum tetrominoShapeEnum)
		: Component(widthPercent, HeightPercent)
	{
		NextTetrominoComponent::LoadTextures();
		_nextTetromino = std::make_unique<Tetromino>(tetrominoShapeEnum);
	}

	NextTetrominoComponent::~NextTetrominoComponent()
	{
	}

	void NextTetrominoComponent::Draw() const
	{
		Component::Draw();
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
		Component::LoadTextures();

		_tetrominosTextures.resize(7);
		_tetrominosTextures[0] = GetTetrominoTexture(AssetsFilePathConsts::TetrominoBlue);
		_tetrominosTextures[1] = GetTetrominoTexture(AssetsFilePathConsts::TetrominoBrown);
		_tetrominosTextures[2] = GetTetrominoTexture(AssetsFilePathConsts::TetrominoGreen);
		_tetrominosTextures[3] = GetTetrominoTexture(AssetsFilePathConsts::TetrominoOrange);
		_tetrominosTextures[4] = GetTetrominoTexture(AssetsFilePathConsts::TetrominoPurple);
		_tetrominosTextures[5] = GetTetrominoTexture(AssetsFilePathConsts::TetrominoRed);
		_tetrominosTextures[6] = GetTetrominoTexture(AssetsFilePathConsts::TetrominoYellow);
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
						, _tetrominosTextures[static_cast<int>(_nextTetromino->GetColor())].get()
						, nullptr, &backgroundTilePosition);

					isEmptyLine = false;
				}
			}
		}
	}
}
