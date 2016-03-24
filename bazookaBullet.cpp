#include "bazookaBullet.h"
#include "SpriteSheet.h"
#include "BatEnemy.h"
#include "GameObjectFactory.h"

GameObject* createBazookaBullet(){
	return new BazookaBullet;
}
static int n = TheGameObjectFactory::Instance()->add(BazookaBullet::staticTypeName(), createBazookaBullet);


void BazookaBullet::draw(){
	m_sprite.draw();
}
void BazookaBullet::update(){
	m_sprite.update();
	checkOffScreen();
}
bool BazookaBullet::load(File* f){
	static SpriteSheet ssBazookaBullet;
	static bool loaded = false;
	if (!loaded){
		ssBazookaBullet = SpriteSheet(Vec2i(1, 1));
		if (!ssBazookaBullet.load("bazookaBullet.png")){
			return false;
		}
		loaded = true;
	}
	m_sprite.setSpriteSheet(&ssBazookaBullet);
	m_sprite.loadAnimation(&ssBazookaBullet, 0, 0, 1);
	return true;
}

const char* BazookaBullet::staticTypeName(){
	return "bazookaBullet";
}
const char* BazookaBullet::getTypeName()const{
	return staticTypeName();
}

const Rect& BazookaBullet::getRect() const{
	return m_sprite.getRect();
}