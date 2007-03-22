#include "SoundManager.hpp"
#include "commons.hpp"
using namespace cs454_2006;

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
  nf(Mix_OpenAudio(audio_rate, audio_format, 
		   audio_channels, audio_buffers),
    "unable to initiate Sound");
  LoadSound(DOT, "resources/sounds/bubble.wav");
  LoadSound(POWERUP, "resources/sounds/powerup.wav");
  LoadSound(GHOST, "resources/sounds/munch.wav");
  LoadSound(GAMEOVER, "resources/sounds/gameover.wav");
  LoadSound(BONUS, "resources/sounds/blibli.wav");
  LoadSound(WALL, "resources/sounds/crack.wav");
  LoadSound(GHOSTEAT, "resources/sounds/crush.wav");
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
  nf(!bgmusic, "Could not load sound file");
  nf(Mix_FadeInChannel(channel, bgmusic, repeats, 3000),
   "Could not fade in channel");
  Mix_VolumeChunk(bgmusic, 64);
}

void SoundManager::MuteChannel(int channelnum){
  Mix_Chunk *chunk = Mix_GetChunk(channelnum);
  nf(!chunk, "Error in getting chunk");
  Mix_VolumeChunk(chunk, 0);
}

void SoundManager::lolChannel(int channelnum, int volume){
  Mix_Chunk *chunk = Mix_GetChunk(channelnum);
  nf(!chunk, "Error in getting chunk");
  Mix_VolumeChunk(chunk, 64);
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
  nf(!effect[_sound], "Could not load sound");
}

void SoundManager::PlayEffect(int channel, sound_t _sound){
  if(effect[_sound])
    nf(Mix_PlayChannel(channel, effect[_sound], 0),
     "Could not play channel");
}

void SoundManager::StopEffect(){
  for(int i=0;i<CHUNKS;++i)
    Mix_FreeChunk(effect[i]);
}
