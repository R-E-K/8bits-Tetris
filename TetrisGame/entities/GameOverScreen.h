#pragma once
#include <memory>
#include "EntitiesConsts.h"
#include "../core/window.h"
#include <SDL2/SDL.h>
#include "../core/SDLDeletersFunctor.h"
#include "../core/SDLMainObjectsProvider.h"
#include "../graphics/DrawTextService.h"

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
