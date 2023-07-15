#include "SimpleBullet.h"
#include "SpriteSheet.h"
#include "BatEnemy.h"
#include "GameObjectFactory.h"

GameObject* createSimpleBullet(){
	return new SimpleBullet;
}
static int n = TheGameObjectFactory::Instance()->add(SimpleBullet::staticTypeName(), createSimpleBullet);


void SimpleBullet::draw(){
	m_sprite.draw();
}
void SimpleBullet::update(){
	m_sprite.update();
	checkOffScreen();
}
bool SimpleBullet::load(File* f){
	static SpriteSheet ssSimpleBullet;
	static bool loaded = false;
	if (!loaded){
		ssSimpleBullet = SpriteSheet(Vec2i(1, 1));
		if (!ssSimpleBullet.load("bullet.png")){
			return false;
		}
		loaded = true;
	}
	m_sprite.setSpriteSheet(&ssSimpleBullet);
	m_sprite.loadAnimation(&ssSimpleBullet, 0, 0, 1);
	return true;
}

const char* SimpleBullet::staticTypeName(){
	return "simpleBullet";
}
const char* SimpleBullet::getTypeName()const{
	return staticTypeName();
}

const Rect& SimpleBullet::getRect() const{
	return m_sprite.getRect();
}