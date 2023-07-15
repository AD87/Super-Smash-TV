#pragma once
#include "Bullet.h"

class SimpleBullet : public Bullet{
public:
	virtual void draw()override;
	virtual void update()override;
	virtual bool load(File* f = nullptr)override;

	static const char* staticTypeName();
	virtual const char* getTypeName()const override;

	virtual const Rect& getRect() const override;
};