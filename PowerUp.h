#pragma once
#include "GameObject.h"
#include "Sprite.h"

class PowerUp : public GameObject{
public:
	virtual ~PowerUp() = 0 {}
	void setPos(const Vec2f& pos);
	virtual void draw() override;
	virtual void update() override;
	virtual const Rect& getRect() const override;
	
protected:
	Sprite m_sprite;
	float m_duration;
	float m_timeRemaining;
};