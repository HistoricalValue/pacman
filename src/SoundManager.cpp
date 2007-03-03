#include "SoundManager.hpp"

//Mix_Chunk *SoundManager::effect;
//x_Chunk *SoundManager::bgmusic;
//int SoundManager::audio_channels, SoundManager::audio_rate,
// SoundManager::audio_buffers;
//Uint16 SoundManager::audio_format;
SoundManager *SoundManager::s = NULL;

SoundManager::SoundManager(void){ 
  audio_rate = 44100;
  audio_format = MIX_DEFAULT_FORMAT;
  audio_channels = 2;
  Mix_AllocateChannels(8);
  audio_buffers = 4096;
  bgmusic = NULL;
  //effect = NULL;
  if(Mix_OpenAudio(audio_rate, audio_format, 
		   audio_channels, audio_buffers)){
    std::cerr<<"unable to initiate Sound"<<std::endl;
  }
  LoadSound(DOT, "resources/sounds/bathos.wav");
  LoadSound(POWERUP, "resources/sounds/powerup.wav");
  LoadSound(GHOST, "resources/sounds/blibli.wav");
  LoadSound(GAMEOVER, "resources/sounds/gameover.wav");
  // one more ghost
  
}

SoundManager *SoundManager::Singleton(void){
  //s.bgmusic = NULL;
  //inits
  if(!s)
    s=new SoundManager();
  return s;
}

//Playing main background music
// -1 for infinite repeats
void SoundManager::Play(int channel, char *file, int repeats){
  bgmusic = Mix_LoadWAV(file);
  Mix_FadeInChannel(channel, bgmusic, repeats, 3000);
  Mix_VolumeChunk(bgmusic, 64);
}

void SoundManager::MuteChannel(int channelnum){
  Mix_VolumeChunk(Mix_GetChunk(channelnum),0);
}

void SoundManager::lolChannel(int channelnum, int volume){
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
void SoundManager::LoadSound(sound_t _sound, char *file){
  effect[_sound] = Mix_LoadWAV(file);
}

void SoundManager::PlayEffect(int channel, sound_t _sound){
  if(effect[_sound])
    Mix_PlayChannel(channel, effect[_sound], 0);
}

void SoundManager::StopEffect(){
  for(int i=0;i<CHUNKS;++i)
    Mix_FreeChunk(effect[i]);
}
