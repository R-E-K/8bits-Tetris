#pragma once
#include <SDL2/SDL_mixer.h>
#include <string>
#include <memory>
#include "SDLDeletersFunctor.h"

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
		std::unique_ptr<Mix_Music, SdlDeleter> currentMusic;
	};

}
