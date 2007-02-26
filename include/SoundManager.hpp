#ifndef _SOUND_MANAGER_H_
#define _SOUND_MANAGER_H_

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>

class SoundManager {
  static Mix_Music* bgmusic;
  static Mix_Chunk* effect;
  static Uint16 audio_format;
  static int audio_channels, audio_rate, audio_buffers;
public:
  SoundManager();
  static SoundManager* Singleton(void);
  void Play(char *file, int repeats);
  void Stop();
  void ChangeState();
  void PlayEffect(char* file);
  void StopEffect();
  ~SoundManager(void);
};


#endif
