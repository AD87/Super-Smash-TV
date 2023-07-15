#pragma once
#include "GameObject.h"
#include "Sprite.h"
#include "SpriteSheet.h"

class MutoidMan : public GameObject {
public:
	virtual void draw() override;
	virtual void update() override;
	virtual bool load(File* f = nullptr)override;

	static const char* staticTypeName();
	virtual const char* getTypeName()const override;

	virtual const Rect& getRect() const override;
	void setPos(const Vec2f& pos);

	void damaged();
	void checkOffScreen();
	void shoot();
private:
	Sprite m_sprite;
	SpriteSheet* m_pss1; 
	SpriteSheet* m_pss2;
	SpriteSheet* m_pss3;
	float m_damagedAnimation;
	float m_animationRemainingTime;
	int m_health;
};