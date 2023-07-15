#pragma once
#include "GameObject.h"
#include "Sprite.h"

class ExplosiveMine : public GameObject {
public:
	virtual void draw() override;
	virtual void update() override;
	virtual bool load(File* f = nullptr)override;

	static const char* staticTypeName();
	virtual const char* getTypeName()const override;

	virtual const Rect& getRect() const override;

	void setPos(const Vec2f& pos);
private:
	Sprite m_sprite;
};