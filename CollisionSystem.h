#pragma once
#include "GameObject.h"

class CollisionSystem{
public:
	virtual ~CollisionSystem(){}
	virtual void checkCollisions(GameObjectMap*) = 0;
};