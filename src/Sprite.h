#pragma once
#include "Vec2.h"
#include "Rect.h"
class SpriteSheet;

class Sprite{
public:
	Sprite();
	virtual ~Sprite(){}
	void draw();
	void update();
	void loadAnimation(SpriteSheet* sh, int minCell, int maxCell, float duration);

	virtual Rect getRect() const;

	void setSpriteSheet(SpriteSheet* ss);
	void setPos(const Vec2f& pos);
	void setVel(const Vec2f& vel);
	void setAcc(const Vec2f& acc);
	const Vec2f& getPos()const;
	const Vec2f& getVel()const;
	const Vec2f& getAcc()const;
	const int& getCurrentCell()const;

private:
	Vec2f m_pos;
	Vec2f m_vel;
	Vec2f m_acc;
	SpriteSheet* m_spriteSheet;
	int m_cell;
	int m_maxCell;
	int m_minCell;
	float m_maxCellTime;//to know how much time we need to change the sprite
	float m_elapsedCellTime;
};