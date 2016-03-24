#include "SpriteSheet.h"
#include "Screen.h"
#include <SDL_Image.h>
#include <assert.h>

SpriteSheet::SpriteSheet(){
	m_numCellsX = 0;
	m_numCellsY = 0;
}

SpriteSheet::SpriteSheet(Vec2i numCells){
	m_numCellsX=numCells.x;
	m_numCellsY=numCells.y;
}

void SpriteSheet::draw(int cellNum, const Vec2f& pos){
	assert(m_sdlTexture);
	int cellWidth = m_size.x / m_numCellsX;
	int cellHeight = m_size.y / m_numCellsY;
	int cellX = cellWidth*(cellNum % m_numCellsX);
	int cellY = cellHeight*(cellNum / m_numCellsX);

	assert(cellX >= 0);
	assert(cellX < m_size.x);

	SDL_Rect source = { cellX, cellY, cellWidth, cellHeight };
	SDL_Rect dest = { (int)pos.x, (int)pos.y, cellWidth, cellHeight };// x,y,width,height
	SDL_RenderCopy(TheScreen::Instance()->getRenderer(), m_sdlTexture, &source, &dest);
}

float SpriteSheet::getCellW() const{
	return static_cast<float>(m_size.x / m_numCellsX);
}
float SpriteSheet::getCellH() const{
	return static_cast<float>(m_size.y / m_numCellsY);
}