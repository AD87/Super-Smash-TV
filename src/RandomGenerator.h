#pragma once
#include <time.h>
#include <algorithm>
#include "Vec2.h"
#include "Singleton.h"

class RandomGenerator : public Uncopyable{
private:
	RandomGenerator();
	friend Singleton<RandomGenerator>;
public:
	bool checkGenerateEnemies();
	int whichDoor();//return 1 of the 4 doors at random
	int numberOfEnemies();
	Vec2f randomPositionBatEnemy(int door);
	bool checkGeneratePowerUps();
	int randomPowerUp();
	Vec2f powerUpPosition();
	
	bool changeDirection();
	Vec2f randomDirection();//random directions for the boss

private:
};

typedef Singleton<RandomGenerator> TheRandomGenerator;