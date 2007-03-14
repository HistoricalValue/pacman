#ifndef _SOUND_MANAGER_H_
#define _SOUND_MANAGER_H_

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>

#define CHUNKS 7
enum sound_t { DOT, POWERUP, GAMEOVER, GHOST, GHOSTEAT, BONUS, WALL };

class SoundManager {
        Mix_Chunk *bgmusic;
	Mix_Chunk *effect[4];
	Uint16 audio_format;
	int audio_channels, audio_rate, audio_buffers;
        static SoundManager *s;
        SoundManager(void);
	public:
	static SoundManager *Singleton(void);
	void Play(int channel, char *file, int repeats);
        void Init();
        void Stop();
        void MuteChannel(int channelnum);
        void lolChannel(int channelnum, int volume);
        void ChangeState();
        void LoadSound(sound_t _sound, char *file);
        void PlayEffect(int channel, sound_t);
	void StopEffect();
	~SoundManager(void);
};


#endif
