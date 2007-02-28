#ifndef _SOUND_MANAGER_H_
#define _SOUND_MANAGER_H_

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>

class SoundManager {
	Mix_Chunk* bgmusic;
	Mix_Chunk* effect;
	Uint16 audio_format;
	int audio_channels, audio_rate, audio_buffers;
        static SoundManager *s;
        SoundManager(void);
	public:
	static SoundManager *Singleton(void);
	void Play(int channel, char *file, int repeats);
	void Stop();
        void MuteChannel(int channelnum);
        void lolChannel(int channelnum);
        void ChangeState();
	void PlayEffect(char* file);
	void StopEffect();
	~SoundManager(void);
};


#endif
