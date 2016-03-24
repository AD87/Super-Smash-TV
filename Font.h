#pragma once
#include <SDL_ttf.h>
#include <string>

class Font{
public:
	Font();
	~Font();
	bool load(const std::string& fontFileName, int pointSize);
	void draw(int x, int y, const std::string& text, SDL_Color& colour);
private:
	TTF_Font* m_font;
};

class Text{
public:
	void setText(const std::string& text);
	void draw(int x, int y);
};