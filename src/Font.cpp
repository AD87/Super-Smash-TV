
#include "Font.h"
#include "Screen.h"

Font::Font(){
	m_font = nullptr;
	//do the init only once
	static bool first = true;
	if (first){
		TTF_Init();
		first = false;
	}
}

Font::~Font(){
	if (m_font){
		TTF_CloseFont(m_font);
	}
}

bool Font::load(const std::string& fontFileName, int pointSize){
	m_font = TTF_OpenFont(fontFileName.c_str(), pointSize);
	return (m_font != nullptr);
}

void Font::draw(int x, int y, const std::string& text, SDL_Color& colour){
	SDL_Surface* surf = TTF_RenderText_Blended(m_font, text.c_str(), colour);

	SDL_Texture* sdlTexture = SDL_CreateTextureFromSurface(TheScreen::Instance()->getRenderer(), surf);
	SDL_Rect rect = { x, y, surf->w, surf->h };
	SDL_RenderCopy(TheScreen::Instance()->getRenderer(), sdlTexture, 0, &rect);
	SDL_FreeSurface(surf);
	SDL_DestroyTexture(sdlTexture);
}