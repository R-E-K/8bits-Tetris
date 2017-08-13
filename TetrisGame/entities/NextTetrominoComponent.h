#pragma once
#include <memory>
#include "EntitiesConsts.h"
#include "Tetromino.h"
#include "../core/window.h"
#include <SDL2/SDL_render.h>
#include "../graphics/ImageLoader.h"
#include "../core/SDLMainObjectsProvider.h"
#include "../core/SDLDeletersFunctor.h"
#include "../graphics/DrawTextService.h"
#include "Component.h"

namespace REKTetrisGame
{
	class NextTetrominoComponent : public Component
	{
	public:
		NextTetrominoComponent(double widthPercent, double HeightPercent, TetrominoShapeEnum tetrominoShapeEnum);
		~NextTetrominoComponent();

		void Draw() const override;

		void SetTetromino(TetrominoShapeEnum tetrominoShapeEnum);
		std::unique_ptr<Tetromino> PopTetromino();

	private:

		std::unique_ptr<Tetromino> _nextTetromino;

		std::vector<std::shared_ptr<SDL_Texture>> TetrominosTextures;

		std::shared_ptr<SDL_Texture> NextTetrominoComponent::GetTetrominoTexture(std::string const& imageFilePath) const;

		void LoadTextures() override;

		void DrawBorder() const override;
		void DrawBackground() const override;
		void DrawTitle() const override;
		void DrawNextTetromino() const;
	};
}
