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

namespace REKTetrisGame
{
	class NextTetrominoComponent
	{
	public:
		NextTetrominoComponent(TetrominoShapeEnum tetrominoShapeEnum);
		~NextTetrominoComponent();

		void Draw() const;

		void SetTetromino(TetrominoShapeEnum tetrominoShapeEnum);
		std::unique_ptr<Tetromino> PopTetromino();

	private:
		int _backgroundTextureWidth;
		int _backgroundTextureHeight;

		std::unique_ptr<Tetromino> _nextTetromino;

		std::unique_ptr<SDL_Texture, SdlDeleter> _borderBackgroundTexture;
		std::unique_ptr<SDL_Texture, SdlDeleter> _backgroundTexture;

		std::vector<std::shared_ptr<SDL_Texture>> TetrominosTextures;

		std::shared_ptr<SDL_Texture> NextTetrominoComponent::GetTetrominoTexture(std::string const& imageFilePath) const;
		void LoadTextures();

		void DrawBorder() const;
		void DrawBackground() const;
		void DrawTitle() const;
		void DrawNextTetromino() const;
	};
}
