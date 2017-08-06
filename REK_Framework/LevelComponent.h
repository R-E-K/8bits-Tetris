#pragma once
#include <memory>
#include "SDLDeletersFunctor.h"
#include "window.h"
#include "DrawTextService.h"
#include "EntitiesConsts.h"

namespace REKFramework
{
	class LevelComponent
	{
	public:
		LevelComponent();
		~LevelComponent();

		void Draw() const;

		void DefineLevel(int nbTotalLinesRemoved);
		int GetLevel() const;

	private:
		int _level;

		int _backgroundTextureWidth;
		int _backgroundTextureHeight;

		std::unique_ptr<SDL_Texture, SdlDeleter> _borderBackgroundTexture;
		std::unique_ptr<SDL_Texture, SdlDeleter> _backgroundTexture;

		void LoadTextures();

		void DrawBorder() const;
		void DrawBackground() const;
		void DrawTitle() const;
		void DrawLevelCounter() const;
	};
}

