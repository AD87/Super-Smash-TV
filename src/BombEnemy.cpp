#include "BombEnemy.h"
#include "SpriteSheet.h"
#include "SimpleBullet.h"
#include "bazookaBullet.h"
#include "GameObjectFactory.h"
#include "Game.h"
#include "File.h"
#include "PlayState.h"
#include "EventPoller.h"
#include "Timer.h"
#include "SoundManager.h"
#include "EnemyBullet.h"
#include "Player.h"
#include "EnemyBlood.h"

GameObject* createBombEnemy(){
	return new BombEnemy;
}
static int n = TheGameObjectFactory::Instance()->add(BombEnemy::staticTypeName(), createBombEnemy);

void collideSimpleBulletBombEnemy(GameObject* go1, GameObject* go2){
	SimpleBullet* bullet = dynamic_cast<SimpleBullet*>(go1);
	assert(bullet);
	BombEnemy* enemy = dynamic_cast<BombEnemy*>(go2);
	assert(enemy);
	bullet->RemoveMe();
	enemy->reduceHealth();
}
static bool b1 = TheGame::Instance()->addCollisionHandler(SimpleBullet::staticTypeName(), BombEnemy::staticTypeName(), collideSimpleBulletBombEnemy);

void collideBazookaBulletBombEnemy(GameObject* go1, GameObject* go2){
	BazookaBullet* bullet = dynamic_cast<BazookaBullet*>(go1);
	assert(bullet);
	BombEnemy* enemy = dynamic_cast<BombEnemy*>(go2);
	assert(enemy);
	enemy->RemoveMe();
	ThePlayState::Instance()->incrementScore(3);
	enemy->showBlood();
}
static bool b2 = TheGame::Instance()->addCollisionHandler(BazookaBullet::staticTypeName(), BombEnemy::staticTypeName(), collideBazookaBulletBombEnemy);

void collidePlayerBombEnemy(GameObject* go1, GameObject* go2){
	Player* player = dynamic_cast<Player*>(go1);
	assert(player);
	BombEnemy* enemy = dynamic_cast<BombEnemy*>(go2);
	assert(enemy);
	enemy->RemoveMe();
	enemy->showBlood();
	if (!ThePlayer::Instance()->isInvincible()){
		ThePlayState::Instance()->decreaseLive();
	}
	else ThePlayState::Instance()->incrementScore(1);
}
static bool b3 = TheGame::Instance()->addCollisionHandler(Player::staticTypeName(), BombEnemy::staticTypeName(), collidePlayerBombEnemy);


void BombEnemy::draw(){
	m_sprite.draw();
}
void BombEnemy::update(){
	m_sprite.update();
	checkOffScreen();
	m_bombTimeRemaining -= TheTimer::Instance()->GetDt();
	if (m_bombTimeRemaining <= 0){
		explode();
	}
}
bool BombEnemy::load(File* file){
	static SpriteSheet ssBombEnemy;
	static bool loaded = false;
	if (!loaded){
		ssBombEnemy = SpriteSheet(Vec2i(1, 1));
		if (!ssBombEnemy.load("boomer.png")){
			return false;
		}
		if (!TheSoundManager::Instance()->load("boomer.wav")){
			return false;
		}
		loaded = true;
	}
	float fx;
	if (!file->getFloat(&fx)){
		return false;
	}
	float fy;
	if (!file->getFloat(&fy)){
		return false;
	}
	m_sprite.setPos(Vec2f(fx, fy));
	m_sprite.loadAnimation(&ssBombEnemy, 0, 0, 1);
	m_health = 10;
	m_bombTimerDuration = 8.0f;
	m_bombTimeRemaining = m_bombTimerDuration;

	return true;
}

const char* BombEnemy::staticTypeName(){
	return "bombEnemy";
}

const char* BombEnemy::getTypeName()const {
	return staticTypeName();
}

const Rect& BombEnemy::getRect() const {
	return m_sprite.getRect();
}

void BombEnemy::reduceHealth(){
	m_health--;
	if (m_health <= 0){
		RemoveMe();
		ThePlayState::Instance()->incrementScore(3);
		showBlood();
	}
}

void BombEnemy::checkOffScreen(){
	float maxX = static_cast<float> (TheScreen::Instance()->getSize().x);
	float maxY = static_cast<float> (TheScreen::Instance()->getSize().y);

	if (m_sprite.getPos().x <= 0 + 50){
		m_sprite.setVel(Vec2f(80, 0));
	}
	if (m_sprite.getPos().x >= maxX - 100){
		m_sprite.setVel(Vec2f(-80, 0));
	}
	if (m_sprite.getPos().y <= 0 + 100){
		m_sprite.setVel(Vec2f(0, 80));
	}
	if (m_sprite.getPos().y >= maxY - 90){
		m_sprite.setVel(Vec2f(0, -80));
	}
}

void BombEnemy::explode(){
	TheSoundManager::Instance()->playSound("boomer.wav");
	RemoveMe();
	Vec2f vecToPlayer(ThePlayer::Instance()->getPos() - m_sprite.getPos());
	Vec2f bulletVel(0, -400);
	for (int i = 0; i < 4; i++){
		Bullet* bullet = dynamic_cast<Bullet*> (TheGameObjectFactory::Instance()->create(EnemyBullet::staticTypeName()));
		bullet->setVel(vecToPlayer);
		bullet->setPos(Vec2f(m_sprite.getPos().x, m_sprite.getPos().y));
		bullet->load();
		static int bulletId = 9999999;
		TheGame::Instance()->addGameObject(bulletId, bullet);
		bulletId--;
		vecToPlayer.x += 30;
		vecToPlayer.y += 30;
	}
}