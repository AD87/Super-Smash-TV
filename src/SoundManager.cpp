#include <cassert>
#include "SoundManager.h"

SoundManager::SoundManager(){
	int audio_rate = 22050;
	Uint16 audio_format = AUDIO_S16SYS;
	int audio_channels = 2;
	int audio_buffers = 4096;

	if (Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers) != 0){
		//fail
	}
}

bool SoundManager::load(const std::string& fileName){
	//load the sound effect for future use
	Mix_Chunk* sound = Mix_LoadWAV(fileName.c_str());
	if (sound){
		chunkmap[fileName] = sound;
		return true;
	}
	return false;
}

void SoundManager::playMusic(const std::string& musicFileName){
	//play background music
	Mix_Music* music = Mix_LoadMUS(musicFileName.c_str());
	assert(music);
	Mix_PlayMusic(music, -1);
}

void SoundManager::stopMusic(){
	Mix_HaltMusic();
}

void SoundManager::playSound(const std::string& fileName){
	//play sound effects
	Mix_Chunk* sound = chunkmap[fileName];

	assert(sound);
	Mix_PlayChannel(-1, sound, 0);
	chunkmap[fileName] = sound;	
}
