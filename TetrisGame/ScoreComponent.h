#pragma once
#include <memory>
#include "SDLDeletersFunctor.h"
#include "SDLMainObjectsProvider.h"
#include "EntitiesConsts.h"
#include "window.h"
#include "DrawTextService.h"

namespace REKFramework
{
	class ScoreComponent
	{
	public:
		ScoreComponent();
		~ScoreComponent();

		void Draw() const;
		void UpdateScore(int level);
		void UpdateScore(int level, int nbLinesJustRemoved);
	private:
		int _score;

		int _backgroundTextureWidth;
		int _backgroundTextureHeight;

		std::unique_ptr<SDL_Texture, SdlDeleter> _borderBackgroundTexture;
		std::unique_ptr<SDL_Texture, SdlDeleter> _backgroundTexture;

		void LoadTextures();

		void DrawBorder() const;
		void DrawBackground() const;
		void DrawTitle() const;
		void DrawScore() const;
	};
}
