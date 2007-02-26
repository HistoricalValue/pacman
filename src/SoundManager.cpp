#include "SoundManager.hpp"

SoundManager* SoundManager::Singleton(void){
  SoundManager* s;
  s->bgmusic = NULL;
  //inits
  s->audio_rate = 22050;
  s->audio_format = AUDIO_S16;
  s->audio_channels = 2;
  s->audio_buffers = 4096;
  s->bgmusic = NULL;
  s->effect = NULL;
  if(Mix_OpenAudio(s->audio_rate, s->audio_format, 
		   s->audio_channels, s->audio_buffers)){
    std::cerr<<"unable to initiate Sound"<<std::endl;
  }
  return s;
}

//Playing main background music
// -1 for infinite repeats
void SoundManager::Play(char* file, int repeats){
  bgmusic = Mix_LoadMUS(file);
  Mix_PlayMusic(bgmusic, repeats);
}

void SoundManager::Stop(){
  //stops the music
  Mix_HaltMusic();
  //freeing the pointer
  Mix_FreeMusic(bgmusic);
  bgmusic = NULL;
}

void SoundManager::ChangeState(){
  if(Mix_PausedMusic())
    Mix_ResumeMusic();
  else
    Mix_PauseMusic();
}
  
void SoundManager::PlayEffect(char* file){
  //loading the effect file
  effect = Mix_LoadWAV(file);
}

void SoundManager::StopEffect(){
  Mix_FreeChunk(effect);
}

