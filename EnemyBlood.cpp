#include "EnemyBlood.h"
#include "GameObjectFactory.h"
#include "SpriteSheet.h"

GameObject* createEnemyBlood(){
	return new EnemyBlood;
}
static int n = TheGameObjectFactory::Instance()->add(EnemyBlood::staticTypeName(), createEnemyBlood);

void EnemyBlood::draw(){
	m_sprite.draw();
}
void EnemyBlood::update(){
	m_sprite.update();
	if (m_sprite.getCurrentCell() == 15){
		RemoveMe();
	}
}
bool EnemyBlood::load(File* file){
	static SpriteSheet ssBlood;
	static bool loaded = false;
	if (!loaded){
		ssBlood = SpriteSheet(Vec2i(4, 4));
		if (!ssBlood.load("blood.png")){
			return false;
		}
		loaded = true;
	}
	m_sprite.setSpriteSheet(&ssBlood);
	m_sprite.loadAnimation(&ssBlood, 0, 15, 1);

	return true;
}

const char* EnemyBlood::staticTypeName(){
	return "enemyBlood";
}
const char* EnemyBlood::getTypeName()const {
	return staticTypeName();
}

const Rect& EnemyBlood::getRect() const {
	return m_sprite.getRect();
}

void EnemyBlood::setPos(const Vec2f& pos){
	m_sprite.setPos(pos);
}