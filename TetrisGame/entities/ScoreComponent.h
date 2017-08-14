#pragma once
#include <memory>
#include "EntitiesConsts.h"
#include "../core/window.h"
#include <SDL2/SDL.h>
#include "../core/SDLDeletersFunctor.h"
#include "../core/SDLMainObjectsProvider.h"
#include "../graphics/DrawTextService.h"
#include "Component.h"
#include <iostream>
#include <fstream>

namespace REKTetrisGame
{
	class ScoreComponent : public Component
	{
	public:
		ScoreComponent(double widthPercent, double HeightPercent);
		~ScoreComponent();

		void Draw() const override;
		void UpdateScore(int level);
		void UpdateScore(int level, int nbLinesJustRemoved);

		void SaveScoreIfBest() const;
	private:
		int _score;
		int _bestScore;

		void InitBestScore();

		void UpdateBestScore();

		void LoadTextures() override;

		void DrawBorder() const override;
		void DrawBackground() const override;
		void DrawTitle() const override;
		void DrawScore() const;
	};
}
