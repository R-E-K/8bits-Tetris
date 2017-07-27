#pragma once
#include <SDL2/SDL_mixer.h>
#include <string>

namespace REKFramework
{
	class SoundManager
	{
	public:
		SoundManager();
		~SoundManager();

		int MusicVolume;

		int Init();
		void LoadMusic(std::string const& filepath, int fadeInDuration);

	private:
		Mix_Music* currentMusic;
	};

}
