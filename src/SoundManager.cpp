#include "SoundManager.hpp"

//Mix_Chunk *SoundManager::effect;
//x_Chunk *SoundManager::bgmusic;
//int SoundManager::audio_channels, SoundManager::audio_rate,
// SoundManager::audio_buffers;
//Uint16 SoundManager::audio_format;
SoundManager *SoundManager::s = NULL;

SoundManager::SoundManager(void){ }

SoundManager *SoundManager::Singleton(void){
  //s.bgmusic = NULL;
  //inits
  if(!s)
    s=new SoundManager();
  s->audio_rate = 22050;
  s->audio_format = MIX_DEFAULT_FORMAT;
  s->audio_channels = 2;
  Mix_AllocateChannels(3);
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
void SoundManager::Play(int channel, char *file, int repeats){
  bgmusic = Mix_LoadWAV(file);
  Mix_PlayChannel(channel, bgmusic, repeats);
  Mix_VolumeChunk(bgmusic, 64);
}

void SoundManager::MuteChannel(int channelnum){
  Mix_VolumeChunk(Mix_GetChunk(channelnum),0);
}

void SoundManager::lolChannel(int channelnum){
  Mix_VolumeChunk(Mix_GetChunk(channelnum),64 );
}

void SoundManager::Stop(){
  //stops the music

   Mix_FreeChunk(bgmusic);
  //freeing the pointer
  //Mix_FreeMusic(bgmusic);
  bgmusic = NULL;
}

void SoundManager::ChangeState(){
  if(Mix_PausedMusic())
    Mix_ResumeMusic();
  else
    Mix_PauseMusic();
}
  
void SoundManager::PlayEffect(char *file){
  //loading the effect file
  effect = Mix_LoadWAV(file);
  Mix_PlayChannel(1, effect, 0);
}

void SoundManager::StopEffect(){
  Mix_FreeChunk(effect);
}
