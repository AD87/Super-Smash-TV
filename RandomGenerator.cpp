#include "RandomGenerator.h"
#include "Screen.h"

RandomGenerator::RandomGenerator(){
	time_t t;
	srand((unsigned int)time(&t));
}

bool RandomGenerator::checkGenerateEnemies(){
	int r = rand();
	int randomNumber = r % 1000 + 1;
	if (randomNumber > 997){
		return true;
	}
	else return false;
}

int RandomGenerator::whichDoor(){
	int r = rand();
	int randomNumber = r % 4 + 1;
	return randomNumber;
}

int RandomGenerator::numberOfEnemies(){
	int r = rand();
	int randomNumber = r % 7 + 1;
	return randomNumber;
}

Vec2f RandomGenerator::randomPositionBatEnemy(int door){
	int r = rand();
	float posX = static_cast<float> (r % 130 + 1);
	r = rand();
	float posY = static_cast<float> (r % 130 + 1);//set a bit different pos for the enemies to make them dont overlap much
	Screen* screen = TheScreen::Instance();
	if (door == 1){
		return Vec2f(0 - posX, screen->getSize().y / 2.0f + 30 - posY);
	}
	else if (door == 2){
		return Vec2f(screen->getSize().x + posX, screen->getSize().y / 2.0f + 30 - posY);
	}
	else if (door == 3){
		return Vec2f(screen->getSize().x / 2.0f + 30 - posX, 0 - posY);
	}
	else {
		return Vec2f(screen->getSize().x / 2.0f + 30 - posX, screen->getSize().y + posY);
	}
}

bool RandomGenerator::checkGeneratePowerUps(){
	int r = rand();
	int randomNumber = r % 1000 + 1;
	if (randomNumber > 999){
		return true;
	}
	else return false;
}

int RandomGenerator::randomPowerUp(){
	int r = rand();
	int randomNumber = r % 5 + 1;
	return randomNumber;
}

Vec2f RandomGenerator::powerUpPosition(){
	int r = rand();
	float posX = static_cast<float> (r % 820 + 50);
	r = rand();
	float posY = static_cast<float> (r % 450 + 110);
	return Vec2f(posX, posY);
}

bool RandomGenerator::changeDirection(){
	int r = rand();
	int randomNumber = r % 1000 + 1;
	if (randomNumber > 996){
		return true;
	}
	else return false;
}

Vec2f RandomGenerator::randomDirection(){
	int r = rand();
	int randomNumber = r % 4 + 1;
	if (randomNumber == 1){
		return Vec2f(100, 0);
	}
	else if (randomNumber == 2){
		return Vec2f(0, 100);
	}
	else if (randomNumber == 3){
		return Vec2f(0, -100);
	}
	else {
		return Vec2f(-100, 0);
	}
}