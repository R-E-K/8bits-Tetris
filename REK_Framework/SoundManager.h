#pragma once
#include <SDL2/SDL_mixer.h>

namespace REKFramework
{
	class SoundManager
	{
	public:
		SoundManager();
		~SoundManager();

		int MusicVolume;

		int Init();
		void LoadMusic(char* filepath, int fadeInDuration);

	private:
		Mix_Music* currentMusic;
	};

}
