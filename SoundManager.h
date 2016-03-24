#pragma once
#include <string>
#include <SDL_mixer.h>
#include <map>
#include "Singleton.h"

#ifdef PlaySound
#undef PlaySound
#endif

class SoundManager:public Uncopyable{
private:
	SoundManager();
	friend class Singleton<SoundManager>;
public:
	bool load(const std::string& fileName);
	void playMusic(const std::string& fileName);
	void stopMusic();
	void playSound(const std::string& fileName);
private:
	typedef std::map<std::string, Mix_Chunk*> ChunkMap;
	ChunkMap chunkmap;
};

typedef Singleton<SoundManager> TheSoundManager;