#include "GameConfiguration.h"
#include "AssetsFilePathConsts.h"

namespace REKTetrisGame
{


	GameConfiguration::GameConfiguration()
	{
		Init();
	}


	GameConfiguration::~GameConfiguration()
	{
	}

	bool GameConfiguration::IsConfigFileFound() const
	{
		return _configFileFound;
	}

	void GameConfiguration::ToggleFullscreenConfig()
	{
		if (_lines.at("Fullscreen") == "1")
		{
			_lines["Fullscreen"] = "0";
		}
		else
		{
			_lines["Fullscreen"] = "1";
		}
		RewriteFile();
	}

	SDL_WindowFlags GameConfiguration::GetFullscreenConfig() const
	{
		// If fullscreen config line is not found, we set windowed mode
		SDL_WindowFlags fullscreenFlag;
		if (_lines.count("Fullscreen") > 0)
		{
			if (_lines.at("Fullscreen") == "1")
			{
				fullscreenFlag = SDL_WINDOW_FULLSCREEN_DESKTOP;
			}
			else
			{
				fullscreenFlag = SDL_WINDOW_SHOWN;
			}
		}
		else
		{
			fullscreenFlag = SDL_WINDOW_SHOWN;
		}

		return fullscreenFlag;
	}

	void GameConfiguration::Init()
	{
		std::string line;
		std::ifstream configFile(AssetsFilePathConsts::ConfigFile);
		SDL_WindowFlags fullscreenFlag;

		if (configFile.is_open())
		{
			_configFileFound = true;
			bool isParam = true;
			ConfigLine configLine;
			while (std::getline(configFile, line, '='))
			{
				std::istringstream iss(line);

				if (isParam)
				{
					configLine.param = line;
				}
				else
				{
					configLine.value = line;
					_lines.insert(std::make_pair(configLine.param, configLine.value));
				}

				isParam = !isParam;
			}
		}
		else
		{
			_configFileFound = false;
		}
	}

	void GameConfiguration::RewriteFile()
	{
		std::ofstream configFile(AssetsFilePathConsts::ConfigFile, std::ofstream::out | std::ofstream::trunc);

		for (auto line : _lines)
		{
			configFile << line.first << "=" << line.second;
		}
		configFile.close();
	}

}