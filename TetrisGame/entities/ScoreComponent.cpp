#include "ScoreComponent.h"
#include "../utils/EncryptDecryptManager.h"

namespace REKTetrisGame
{
	ScoreComponent::ScoreComponent(double widthPercent, double HeightPercent)
		: Component(widthPercent, HeightPercent)
	{
		_backgroundTextureWidth /= EntitiesConsts::NB_ROWS;
		ScoreComponent::LoadTextures();
		_score = 0;
		InitBestScore();
	}


	ScoreComponent::~ScoreComponent()
	{
	}

	void ScoreComponent::Draw() const
	{
		Component::Draw();
		DrawScore();
	}

	void ScoreComponent::UpdateScore(int level)
	{
		_score += level * 100;
		UpdateBestScore();
	}

	void ScoreComponent::UpdateScore(int level, int nbLinesJustRemoved)
	{
		switch (nbLinesJustRemoved)
		{
		case 1:
			_score += (1000 * level) * nbLinesJustRemoved;
			break;
		case 2:
			_score += (2000 * level) * nbLinesJustRemoved;
			break;
		case 3:
			_score += (5000 * level) * nbLinesJustRemoved;
			break;
		case 4:
			_score += (10000 * level) * nbLinesJustRemoved;
			break;
		}

		UpdateBestScore();
	}

	void ScoreComponent::SaveScoreIfBest() const
	{
		// Open score file and delete previous score with "std::ofstream::out | std::ofstream::trunc"
		std::ofstream scoreFile ("system.rek", std::ofstream::out | std::ofstream::trunc);

		auto cryptedScore = EncryptDecryptManager::EncryptDecryptString(std::to_string(_score));

		scoreFile << cryptedScore;
		scoreFile.close();

	}

	void ScoreComponent::InitBestScore()
	{
		std::string cryptedSavedScore;
		std::ifstream scoreFile("system.rek");
		if (scoreFile.is_open())
		{
			std::getline(scoreFile, cryptedSavedScore);

			auto decryptedScore = EncryptDecryptManager::EncryptDecryptString(cryptedSavedScore);

			_bestScore = std::stoi(decryptedScore);
		}
		else
		{
			_bestScore = 0;
		}

		scoreFile.close();
	}

	void ScoreComponent::UpdateBestScore()
	{
		if (_score > _bestScore)
		{
			_bestScore = _score;
		}
	}

	void ScoreComponent::LoadTextures()
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
	}

	void ScoreComponent::DrawBorder() const
	{
		SDL_Rect backgroundTilePosition;
		backgroundTilePosition.x = (SCREEN_WIDTH / 2) - ((_backgroundTextureWidth * EntitiesConsts::NB_COLUMNS) / 2) + _backgroundTextureWidth - EntitiesConsts::BORDER_THICKNESS;
		backgroundTilePosition.y = SCREEN_HEIGHT * (2.0 / 100.0) - EntitiesConsts::BORDER_THICKNESS; // Start at 2% from top
		backgroundTilePosition.w = (_backgroundTextureWidth * EntitiesConsts::NB_COLUMNS) + (EntitiesConsts::BORDER_THICKNESS * 2);
		backgroundTilePosition.h = (_backgroundTextureHeight * 1) + (EntitiesConsts::BORDER_THICKNESS * 2);

		SDL_RenderCopy(SDLMainObjectsProvider::GetRendererRawPointer()
			, _borderBackgroundTexture.get()
			, nullptr, &backgroundTilePosition);
	}

	void ScoreComponent::DrawBackground() const
	{
		int backgroundTileXInitPosition = (SCREEN_WIDTH / 2) - ((_backgroundTextureWidth * EntitiesConsts::NB_COLUMNS) / 2) + _backgroundTextureWidth;

		SDL_Rect backgroundTilePosition;
		backgroundTilePosition.x = backgroundTileXInitPosition;
		backgroundTilePosition.y = SCREEN_HEIGHT * (2.0 / 100.0);
		backgroundTilePosition.w = (_backgroundTextureWidth * EntitiesConsts::NB_COLUMNS);
		backgroundTilePosition.h = (_backgroundTextureHeight * 1);

		SDL_RenderCopy(SDLMainObjectsProvider::GetRendererRawPointer()
			, _backgroundTexture.get()
			, nullptr, &backgroundTilePosition);
	}

	void ScoreComponent::DrawTitle() const
	{
		SDL_Color color = { 255, 255, 255 };

		DrawTextService::DrawTextWithSizeAndColor("Best"
			, (SCREEN_WIDTH / 2) - ((_backgroundTextureWidth * EntitiesConsts::NB_COLUMNS) / 2) + _backgroundTextureWidth + (_backgroundTextureWidth * (30.0 / 100.0))
			, SCREEN_HEIGHT * (1.5 / 100.0)
			, _backgroundTextureHeight * (60.0 / 100.0)
			, color);

		DrawTextService::DrawTextWithSizeAndColor("Score"
			, (SCREEN_WIDTH / 2) - ((_backgroundTextureWidth * EntitiesConsts::NB_COLUMNS) / 2) + _backgroundTextureWidth + (_backgroundTextureWidth * (30.0 / 100.0))
			, SCREEN_HEIGHT * (1.5 / 100.0) + _backgroundTextureHeight * (50.0 / 100.0)
			, _backgroundTextureHeight * (60.0 / 100.0)
			, color);
	}

	void ScoreComponent::DrawScore() const
	{
		SDL_Color color = { 50, 50, 255 };
		SDL_Color colorBestScore = { 255, 50, 50 };
		SDL_Color colorNewbestScore = { 50, 255, 50 };

		DrawTextService::DrawTextWithSizeAndColor(std::to_string(_bestScore)
			, (SCREEN_WIDTH / 2) - ((_backgroundTextureWidth * EntitiesConsts::NB_COLUMNS) / 2) + _backgroundTextureWidth + (_backgroundTextureWidth * (30.0 / 100.0)) + (_backgroundTextureHeight * (45.0 / 100.0) * 5)
			, SCREEN_HEIGHT * (1.5 / 100.0)
			, _backgroundTextureHeight * (60.0 / 100.0)
			, (_score < _bestScore) ? colorBestScore : colorNewbestScore);

		DrawTextService::DrawTextWithSizeAndColor(std::to_string(_score)
			, (SCREEN_WIDTH / 2) - ((_backgroundTextureWidth * EntitiesConsts::NB_COLUMNS) / 2) + _backgroundTextureWidth + (_backgroundTextureWidth * (30.0 / 100.0)) + (_backgroundTextureHeight * (45.0 / 100.0) * 5)
			, SCREEN_HEIGHT * (1.5 / 100.0) + _backgroundTextureHeight * (50.0 / 100.0)
			, _backgroundTextureHeight * (60.0 / 100.0)
			, color);
	}
}
