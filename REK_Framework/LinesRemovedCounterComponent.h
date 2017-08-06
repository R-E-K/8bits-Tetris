#pragma once
#include <memory>
#include "SDLDeletersFunctor.h"
#include "window.h"
#include "SDLMainObjectsProvider.h"
#include "EntitiesConsts.h"
#include "DrawTextService.h"

namespace REKFramework
{
	class LinesRemovedCounterComponent
	{
	public:
		LinesRemovedCounterComponent();
		~LinesRemovedCounterComponent();

		void Draw() const;

		void AddNumberOfLinesRemovedToCounter(int nbLinesRemoved);
		int GetLinesRemovedCounter() const;

	private:
		int _countLinesRemoved;

		int _backgroundTextureWidth;
		int _backgroundTextureHeight;

		std::unique_ptr<SDL_Texture, SdlDeleter> _borderBackgroundTexture;
		std::unique_ptr<SDL_Texture, SdlDeleter> _backgroundTexture;

		void LoadTextures();

		void DrawBorder() const;
		void DrawBackground() const;
		void DrawTitle() const;
		void DrawLinesRemovedCounter() const;
	};
}