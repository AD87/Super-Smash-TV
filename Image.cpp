#include "Image.h"
#include "Screen.h"
#include <SDL_Image.h>
#include <assert.h>

Image::Image(){
	m_sdlTexture = nullptr;
}

bool Image::load(const std::string& fileName){
	SDL_Surface* image = IMG_Load(fileName.c_str());
	assert(image);
	m_size = Vec2i(image->w, image->h);
	m_sdlTexture = SDL_CreateTextureFromSurface(TheScreen::Instance()->getRenderer(), image);
	SDL_FreeSurface(image);
	return (m_sdlTexture != nullptr);
}

void Image::draw(const Vec2f& pos){
	assert(m_sdlTexture);
	SDL_Rect rect = { static_cast<int>(pos.x), static_cast<int>(pos.y), 
		static_cast<int>(m_size.x), static_cast<int>(m_size.y) };// x,y,width,height
	SDL_RenderCopy(TheScreen::Instance()->getRenderer(), m_sdlTexture, 0, &rect);
}
