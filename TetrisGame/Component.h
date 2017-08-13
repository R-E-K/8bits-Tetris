#pragma once
#include "core/SDLDeletersFunctor.h"
#include <memory>
#include "core/window.h"
#include "core/SDLMainObjectsProvider.h"
#include "entities/EntitiesConsts.h"

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

