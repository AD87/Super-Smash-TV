#pragma once
#include "Enemy.h"

class BombEnemy : public Enemy{
public:
	virtual void draw() override;
	virtual void update() override;
	virtual bool load(File* f = nullptr)override;

	static const char* staticTypeName();
	virtual const char* getTypeName()const override;

	virtual const Rect& getRect() const override;

	void reduceHealth();
private:
	void checkOffScreen();
	void explode();//kill itself and shoot bullets to the player

	int m_health;
	float m_bombTimerDuration;
	float m_bombTimeRemaining;
};