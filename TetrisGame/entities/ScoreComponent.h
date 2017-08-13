#pragma once
#include <memory>
#include "EntitiesConsts.h"
#include "../core/window.h"
#include <SDL2/SDL.h>
#include "../core/SDLDeletersFunctor.h"
#include "../core/SDLMainObjectsProvider.h"
#include "../graphics/DrawTextService.h"

namespace REKTetrisGame
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
