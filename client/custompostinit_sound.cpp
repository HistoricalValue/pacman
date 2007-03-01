#include "CustomPostinit_Commons.hpp"
#include "SoundManager.hpp"

CPI_DEFINE(custompostinit_sound) {
	// Sound set up
	
	SoundManager::Singleton()->
	 Play(0, "resources/sounds/bobos2.wav", -1);
	SoundManager::Singleton()->lolChannel(0, 36);
	SoundManager::Singleton()->
	 Play(1, "resources/sounds/maskdream.wav", -1);
       	SoundManager::Singleton()->MuteChannel(1);
//	SoundManager::Singleton()->
//	 PlayEffect("resources/sounds/bobos.wav");

}
