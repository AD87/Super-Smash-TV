#pragma once
#include <string>
#include <SDL.h>
#include "Vec2.h"
#include "Singleton.h"

class Screen;

class Screen:public Uncopyable{
private:
	Screen();
	friend Singleton<Screen>;
public:
	bool createWindow(std::string name, int width, int height);//make it bool to return false if something went wrong
	bool createWindow(std::string name, Vec2i size);
	void flipBuffer();
	SDL_Renderer* getRenderer();
	const Vec2i& getSize()const;

private:
	SDL_Renderer* m_renderer;
	Vec2i m_size;
};

typedef Singleton<Screen> TheScreen;