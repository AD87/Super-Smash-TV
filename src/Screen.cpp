#include "Screen.h"
#include <cassert>

Screen::Screen(){
	m_renderer = nullptr;
}

bool Screen::createWindow(std::string name, int width, int height){
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window* window = SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, 0); //SDL_WINDOW_FULLSCREEN);
	if (!window)return false;
	m_renderer = SDL_CreateRenderer(window, -1, 0);
	m_size = Vec2i(width, height);
	return (m_renderer != nullptr);
}

bool Screen::createWindow(std::string name, Vec2i size){
	return createWindow(name, size.x, size.y);
}

void Screen::flipBuffer(){
	SDL_RenderPresent(m_renderer);
}

SDL_Renderer* Screen::getRenderer(){
	return m_renderer;
}

const Vec2i& Screen::getSize()const{
	return m_size;
}
