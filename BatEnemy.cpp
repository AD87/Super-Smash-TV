#include "BatEnemy.h"
#include "SpriteSheet.h"
#include "File.h"
#include "SimpleBullet.h"
#include "bazookaBullet.h"
#include "GameObjectFactory.h"
#include "Game.h"
#include "PlayState.h"
#include "EventPoller.h"
#include "Player.h"
#include "EnemyBlood.h"

GameObject* createBatEnemy(){
	return new BatEnemy;
}
static int n = TheGameObjectFactory::Instance()->add(BatEnemy::staticTypeName(), createBatEnemy);

void collideSimpleBulletEnemy(GameObject* go1, GameObject* go2){
	SimpleBullet* bullet = dynamic_cast<SimpleBullet*>(go1);
	assert(bullet);
	BatEnemy* enemy = dynamic_cast<BatEnemy*>(go2);
	assert(enemy);
	bullet->RemoveMe();
	ThePlayState::Instance()->incrementScore(1);
	enemy->RemoveMe();
	enemy->showBlood();
}
static bool b1 = TheGame::Instance()->addCollisionHandler(SimpleBullet::staticTypeName(), BatEnemy::staticTypeName(), collideSimpleBulletEnemy);
//populate the collision map at the beginning of the game

void collideBazookaBulletEnemy(GameObject* go1, GameObject* go2){
	BazookaBullet* bullet = dynamic_cast<BazookaBullet*>(go1);
	assert(bullet);
	BatEnemy* enemy = dynamic_cast<BatEnemy*>(go2);
	assert(enemy);
	enemy->RemoveMe();
	ThePlayState::Instance()->incrementScore(1);
	enemy->showBlood();
}
static bool b2 = TheGame::Instance()->addCollisionHandler(BazookaBullet::staticTypeName(), BatEnemy::staticTypeName(), collideBazookaBulletEnemy);

void collidePlayerEnemy(GameObject* go1, GameObject* go2){
	Player* player = dynamic_cast<Player*>(go1);
	assert(player);
	BatEnemy* enemy = dynamic_cast<BatEnemy*>(go2);
	assert(enemy);
	enemy->RemoveMe();
	enemy->showBlood();
	if (!ThePlayer::Instance()->isInvincible()){
		ThePlayState::Instance()->decreaseLive();
	}
	else ThePlayState::Instance()->incrementScore(1);
}
static bool b3 = TheGame::Instance()->addCollisionHandler(Player::staticTypeName(), BatEnemy::staticTypeName(), collidePlayerEnemy);


void BatEnemy::draw(){
	m_sprite.draw();
}
void BatEnemy::update(){
	followPlayer();
	changeAnimation();
	m_sprite.update();
}
bool BatEnemy::load(File* f){
	static bool loaded = false;
	static SpriteSheet ssBatEnemy(Vec2i(9, 4));
	m_pssBatEnemy = &ssBatEnemy;
	if (!loaded){
		if (!ssBatEnemy.load("skeletons.png")){
			return false;
		}
		loaded = true;
	}
	m_sprite.setSpriteSheet(&ssBatEnemy);
	m_lastAnimation = 0;

	return true;
}

const char* BatEnemy::staticTypeName(){
	return "batEnemy";
}

const char* BatEnemy::getTypeName()const {
	return staticTypeName();
}

const Rect& BatEnemy::getRect() const {
	return m_sprite.getRect().scale(0.6f);
}

void BatEnemy::followPlayer(){
	Player* p = ThePlayer::Instance();
	float directionX = p->getPos().x - m_sprite.getPos().x;
	float directionY = p->getPos().y - m_sprite.getPos().y;
	float length = sqrt(directionX*directionX + directionY*directionY);
	float normLength = 1 / length;
	directionX *= normLength;
	directionY *= normLength;
	m_sprite.setVel(Vec2f(directionX*100.0f, directionY*100.0f));
}

void BatEnemy::changeAnimation(){
	Player* p = ThePlayer::Instance();
	if (m_sprite.getPos().x > p->getPos().x){

		if (m_lastAnimation != 1)m_sprite.loadAnimation(m_pssBatEnemy, 9, 17, 1);
		m_lastAnimation = 1;
	}
	else if (m_sprite.getPos().x < p->getPos().x){
		if (m_lastAnimation != 2)m_sprite.loadAnimation(m_pssBatEnemy, 27, 35, 1);
		m_lastAnimation = 2;
	}
}