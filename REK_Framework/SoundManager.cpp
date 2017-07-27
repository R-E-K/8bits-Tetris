#include "SoundManager.h"

namespace REKFramework
{
	SoundManager::SoundManager()
	{
		currentMusic = nullptr;
		MusicVolume = MIX_MAX_VOLUME;
	}


	SoundManager::~SoundManager()
	{
		Mix_FreeMusic(currentMusic);

		// https://www.libsdl.org/projects/SDL_mixer/docs/SDL_mixer_10.html#SEC10
		// Since each call to Mix_Init may set different flags, there is no way, currently, 
		// to request how many times each one was initted. In other words, 
		// the only way to quit for sure is to do a loop :
		while (Mix_Init(0))
			Mix_Quit();
	}

	int SoundManager::Init()
	{
		int SDLMixerInitFlags = MIX_INIT_OGG;
		int result = Mix_Init(SDLMixerInitFlags);

		if (result == 0)
			return -1;

		// Check all flags setted up and not just at least one (not just checking for 0 as before)
		if (result & SDLMixerInitFlags != SDLMixerInitFlags)
			return -1;

		Mix_VolumeMusic(MusicVolume);
		Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024);
	}

	void SoundManager::LoadMusic(std::string const& filepath, int fadeInDuration)
	{
		currentMusic = Mix_LoadMUS("resources/songs/MUS_N_CD_1.ogg");
		if (currentMusic != nullptr)
		{
			Mix_FadeInMusic(currentMusic, -1, fadeInDuration);
		}
	}
}
