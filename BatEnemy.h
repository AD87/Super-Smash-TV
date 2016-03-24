#pragma once
#include "Enemy.h"
#include "SpriteSheet.h"

class BatEnemy : public Enemy{
public:
	virtual void draw() override;
	virtual void update() override;
	virtual bool load(File* f = nullptr)override;

	static const char* staticTypeName();
	virtual const char* getTypeName()const override;

	virtual const Rect& getRect() const override;
private:
	void followPlayer();
	void changeAnimation();

	SpriteSheet* m_pssBatEnemy;
	int m_lastAnimation;
};