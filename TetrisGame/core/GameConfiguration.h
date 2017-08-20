#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <SDL2/SDL_video.h>
#include <sstream>
#include <iterator>
#include <algorithm>
#include <map>

namespace REKTetrisGame
{
	struct ConfigLine
	{
		std::string param;
		std::string value;
	};

	class GameConfiguration
	{
	public:
		GameConfiguration();
		~GameConfiguration();

		bool IsConfigFileFound() const;

		void ToggleFullscreenConfig();
		SDL_WindowFlags GetFullscreenConfig() const;

	private:
		void Init();
		void RewriteFile();

		std::map<std::string, std::string> _lines;
		bool _configFileFound;
	};
}