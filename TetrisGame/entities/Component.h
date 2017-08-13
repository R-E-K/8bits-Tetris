#pragma once
#include <memory>
#include <SDL2/SDL_render.h>
#include "../core/SDLDeletersFunctor.h"
#include "../core/window.h"
#include "../core/SDLMainObjectsProvider.h"
#include "EntitiesConsts.h"

namespace REKTetrisGame
{
	class Component
	{
	public:
		Component(double widthPercent, double HeightPercent);
		~Component();

		virtual void Draw() const = 0;

	protected:
		int _backgroundTextureWidth;
		int _backgroundTextureHeight;

		std::unique_ptr<SDL_Texture, SdlDeleter> _borderBackgroundTexture;
		std::unique_ptr<SDL_Texture, SdlDeleter> _backgroundTexture;

		virtual void LoadTextures();

		virtual void DrawBorder() const;
		virtual void DrawBackground() const;
		virtual void DrawTitle() const;
	};
}

