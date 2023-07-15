#pragma once
#include "GameObject.h"
#include "Sprite.h"


class Bullet : public GameObject{
public:
	virtual ~Bullet() {}
	void setPos(const Vec2f& pos);
	void setVel(const Vec2f& vel);
protected:
	void checkOffScreen();
	Sprite m_sprite;
};
