#include "SoundManager.h"

namespace REKTetrisGame
{
	SoundManager::SoundManager()
	{
		_currentMusic = nullptr;
		_currentSoundChannels[0] = nullptr;
		_currentSoundChannels[1] = nullptr;

		MusicVolume = MIX_MAX_VOLUME;
		SoundVolume = MIX_MAX_VOLUME;
	}


	SoundManager::~SoundManager()
	{
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
		if ((result & SDLMixerInitFlags) != SDLMixerInitFlags)
			return -1;

		Mix_VolumeMusic(MusicVolume);
		Mix_Volume(1, SoundVolume);

		Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096);
		return 0;
	}

	void SoundManager::PlayMusic(std::string const& filepath, int fadeInDuration)
	{
		_currentMusic = std::unique_ptr<Mix_Music, SdlDeleter>(
			Mix_LoadMUS(filepath.c_str()),
			SdlDeleter()
			);

		if (_currentMusic != nullptr)
		{
			Mix_FadeInMusic(_currentMusic.get(), -1, fadeInDuration);
		}
	}

	void SoundManager::PlaySound(std::string const& filepath, int channel)
	{
		_currentSoundChannels[channel - 1] = std::unique_ptr<Mix_Chunk, SdlDeleter>(
			Mix_LoadWAV(filepath.c_str()),
			SdlDeleter()
			);

		Mix_PlayChannel(channel, _currentSoundChannels[channel - 1].get(), 0);
	}
}
