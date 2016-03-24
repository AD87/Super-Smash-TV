#pragma once
#include <string>
#include "Vec2.h"

struct SDL_Texture;
class Screen; //forward declaration

class Image{
public:
	Image();
	bool load(const std::string& fileName);
	void draw(const Vec2f& pos);

protected:
	SDL_Texture* m_sdlTexture;
	Vec2i m_size;
};