#include "EnemyBullet.h"
#include "SpriteSheet.h"
#include "Player.h"
#include "Game.h"
#include "PlayState.h"
#include "GameObjectFactory.h"

GameObject* createEnemyBullet(){
	return new EnemyBullet;
}
static int n = TheGameObjectFactory::Instance()->add(EnemyBullet::staticTypeName(), createEnemyBullet);

void collideEnemyBulletPlayer(GameObject* go1, GameObject* go2){
	EnemyBullet* bullet = dynamic_cast<EnemyBullet*>(go1);
	assert(bullet);
	Player* player = dynamic_cast<Player*>(go2);
	assert(player);
	bullet->RemoveMe();
	if (!ThePlayer::Instance()->isInvincible()){
		ThePlayState::Instance()->decreaseLive();
	}
}
static bool b1 = TheGame::Instance()->addCollisionHandler(EnemyBullet::staticTypeName(), Player::staticTypeName(), collideEnemyBulletPlayer);


void EnemyBullet::draw(){
	m_sprite.draw();
}
void EnemyBullet::update(){
	m_sprite.update();
	checkOffScreen();
}
bool EnemyBullet::load(File* f){
	static SpriteSheet ssEnemyBullet;
	static bool loaded = false;
	if (!loaded){
		ssEnemyBullet = SpriteSheet(Vec2i(1, 1));
		if (!ssEnemyBullet.load("enemyBullet.png")){
			return false;
		}
		loaded = true;
	}
	m_sprite.setSpriteSheet(&ssEnemyBullet);
	m_sprite.loadAnimation(&ssEnemyBullet, 0, 0, 1);
	return true;
}

const char* EnemyBullet::staticTypeName(){
	return "enemyBullet";
}
const char* EnemyBullet::getTypeName()const{
	return staticTypeName();
}

const Rect& EnemyBullet::getRect() const{
	return m_sprite.getRect();
}