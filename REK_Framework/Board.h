#pragma once
#include <SDL2/SDL.h>
#include <memory>
#include <vector>

namespace REKFramework
{
	class Board
	{
	public:
		Board();
		~Board();

		void DrawBackground() const;

	private:

		const Uint8 NB_COLUMNS = 10;
		const Uint8 NB_ROWS = 18;

		std::shared_ptr<SDL_Texture> lightBackgroundTexture;
		std::shared_ptr<SDL_Texture> darkBackgroundTexture;

		int backgroundTextureWidth;
		int backgroundTextureHeight;

		// TODO : Maybe Boost Multi Array could be interesting
		//std::vector<std::vector<std::shared_ptr<SDL_Texture>>> backgroundArray;

		void SetTexturesBackground();
	};

}
