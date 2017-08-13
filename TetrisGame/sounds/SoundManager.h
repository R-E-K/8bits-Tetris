#pragma once
#include <SDL2/SDL_mixer.h>
#include <string>
#include <memory>
#include "../core/SDLDeletersFunctor.h"

namespace REKTetrisGame
{
	class SoundManager
	{
	public:
		SoundManager();
		~SoundManager();

		int MusicVolume;
		int SoundVolume;

		int Init();

		void PlayMusic(std::string const& filepath, int fadeInDuration);
		void PlaySound(std::string const& filepath, int channel);

	private:
		std::unique_ptr<Mix_Music, SdlDeleter> currentMusic;

		// The sound need to be in RAM to be played
		// So we stock it or it will be deleted at the end of PlaySound()
		std::unique_ptr<Mix_Chunk, SdlDeleter> currentSoundChannels[2];
	};

}
