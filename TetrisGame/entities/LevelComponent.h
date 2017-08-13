#pragma once
#include <memory>
#include "EntitiesConsts.h"
#include "../core/window.h"
#include <SDL2/SDL.h>
#include "../core/SDLDeletersFunctor.h"
#include "../core/SDLMainObjectsProvider.h"
#include "../graphics/DrawTextService.h"
#include "Component.h"

namespace REKTetrisGame
{
	class LevelComponent : public Component
	{
	public:
		LevelComponent(double widthPercent, double HeightPercent);
		~LevelComponent();

		void Draw() const override;

		void DefineLevel(int nbTotalLinesRemoved);
		int GetLevel() const;

	private:
		int _level;

		void DrawBorder() const override;
		void DrawBackground() const override;
		void DrawTitle() const override;
		void DrawLevelCounter() const;
	};
}

