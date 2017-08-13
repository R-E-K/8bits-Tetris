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
	class LinesRemovedCounterComponent : public Component
	{
	public:
		LinesRemovedCounterComponent(double widthPercent, double HeightPercent);
		~LinesRemovedCounterComponent();

		void Draw() const override;

		void AddNumberOfLinesRemovedToCounter(int nbLinesRemoved);
		int GetLinesRemovedCounter() const;

	private:
		int _countLinesRemoved;

		void LoadTextures() override;

		void DrawBorder() const override;
		void DrawBackground() const override;
		void DrawTitle() const override;
		void DrawLinesRemovedCounter() const;
	};
}
