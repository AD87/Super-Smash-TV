#pragma once
#include "Image.h"

class SpriteSheet:public Image{
public:
	SpriteSheet();
	SpriteSheet(Vec2i numCells);
	void draw(int cellnum, const Vec2f& pos);

	float getCellW() const;
	float getCellH() const;
protected:
	int m_numCellsX;
	int m_numCellsY;
};