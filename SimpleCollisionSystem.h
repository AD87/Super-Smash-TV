#pragma once

#include "CollisionSystem.h"

class SimpleCollisionSystem : public CollisionSystem{
public:
	virtual void checkCollisions(GameObjectMap* gos)override;

};