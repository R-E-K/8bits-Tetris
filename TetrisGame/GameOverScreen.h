#pragma once
#include <memory>
#include "SDLDeletersFunctor.h"
#include "window.h"
#include "SDLMainObjectsProvider.h"
#include "EntitiesConsts.h"
#include "DrawTextService.h"

namespace REKFramework
{
	class GameOverScreen
	{
	public:
		GameOverScreen();
		~GameOverScreen();

		void Draw() const;

	private:

		std::unique_ptr<SDL_Texture, SdlDeleter> _backgroundTexture;
		SDL_Rect _backgroundTextureRect;

		void LoadTextures();

		void DrawBackground() const;
		void DrawText() const;
	};
}
