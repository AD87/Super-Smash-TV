#include "MutoidMan.h"
#include "SpriteSheet.h"
#include "Player.h"
#include "Game.h"
#include "EventPoller.h"
#include "Timer.h"
#include "SimpleBullet.h"
#include "bazookaBullet.h"
#include "EnemyBullet.h"
#include "BatEnemy.h"
#include "RandomGenerator.h"
#include "GameObjectFactory.h"
#include "PlayState.h"
#include "File.h"

GameObject* createMutoidMan(){
	return new MutoidMan;
}
static int n = TheGameObjectFactory::Instance()->add(MutoidMan::staticTypeName(), createMutoidMan);

void collideSimpleBulletMutoidMan(GameObject* go1, GameObject* go2){
	SimpleBullet* bullet = dynamic_cast<SimpleBullet*>(go1);
	assert(bullet);
	MutoidMan* mutoid = dynamic_cast<MutoidMan*>(go2);
	assert(mutoid);
	mutoid->damaged();
	ThePlayState::Instance()->incrementScore(2);
	bullet->RemoveMe();
}
static bool b1 = TheGame::Instance()->addCollisionHandler(SimpleBullet::staticTypeName(), MutoidMan::staticTypeName(), collideSimpleBulletMutoidMan);

void collideBazookaBulletMutoidMan(GameObject* go1, GameObject* go2){
	BazookaBullet* bullet = dynamic_cast<BazookaBullet*>(go1);
	assert(bullet);
	MutoidMan* mutoid = dynamic_cast<MutoidMan*>(go2);
	assert(mutoid);
	mutoid->damaged();
	ThePlayState::Instance()->incrementScore(2);
	bullet->RemoveMe();
}
static bool b2 = TheGame::Instance()->addCollisionHandler(BazookaBullet::staticTypeName(), MutoidMan::staticTypeName(), collideBazookaBulletMutoidMan);

void collidePlayerMutoidMan(GameObject* go1, GameObject* go2){
	Player* player = dynamic_cast<Player*>(go1);
	assert(player);
	MutoidMan* mutoid = dynamic_cast<MutoidMan*>(go2);
	assert(mutoid);
	if (!ThePlayer::Instance()->isInvincible()){
		ThePlayState::Instance()->decreaseLive();
	}
	else player->setPos(Vec2f(player->getPos().x - 10, player->getPos().y));
	//if collide with the boss in invincible mode we are push away to the left
}
static bool b3 = TheGame::Instance()->addCollisionHandler(Player::staticTypeName(), MutoidMan::staticTypeName(), collidePlayerMutoidMan);

void collideMutoidManBatEnemy(GameObject* go1, GameObject* go2){
	BatEnemy* enemy = dynamic_cast<BatEnemy*>(go1);
	assert(enemy);
	MutoidMan* mutoid = dynamic_cast<MutoidMan*>(go2);
	assert(mutoid);
	enemy->RemoveMe();
	enemy->showBlood();
}
static bool b4 = TheGame::Instance()->addCollisionHandler(BatEnemy::staticTypeName(), MutoidMan::staticTypeName(), collideMutoidManBatEnemy);

void MutoidMan::draw(){
	m_sprite.draw();
}
void MutoidMan::update(){
	m_sprite.update();

	RandomGenerator* rGen = TheRandomGenerator::Instance();
	if (rGen->changeDirection()){
		m_sprite.setVel(rGen->randomDirection());
	}	

	checkOffScreen();

	m_animationRemainingTime -= TheTimer::Instance()->GetDt();
	if (m_animationRemainingTime <= 0){
		m_animationRemainingTime = m_damagedAnimation;
		//load normal animation
		if (m_health <= 66){
			if (m_health <= 33){
				m_sprite.loadAnimation(m_pss3, 0, 0, 1);
			}
			else {
				m_sprite.loadAnimation(m_pss2, 0, 0, 1);
			}
		}
		else m_sprite.loadAnimation(m_pss1, 0, 0, 1);
	}
}
bool MutoidMan::load(File* file){
	static bool loaded = false;
	static SpriteSheet ssMutoid1(Vec2i(2, 1));
	static SpriteSheet ssMutoid2(Vec2i(2, 1));
	static SpriteSheet ssMutoid3(Vec2i(2, 1));
	m_pss1 = &ssMutoid1;
	m_pss2 = &ssMutoid2;
	m_pss3 = &ssMutoid3;
	if (!loaded){
		if (!ssMutoid1.load("mm1.png")){
			return false;
		}
		if (!ssMutoid2.load("mm2.png")){
			return false;
		}
		if (!ssMutoid3.load("mm3.png")){
			return false;
		}
		loaded = true;
	}
	m_sprite.loadAnimation(&ssMutoid1, 0, 0, 1);
	m_damagedAnimation = 1.0f;

	float fx;
	if (!file->getFloat(&fx)){
		return false;
	}
	float fy;
	if (!file->getFloat(&fy)){
		return false;
	}
	m_sprite.setPos(Vec2f(fx, fy));
	m_health = 100;
	m_sprite.getRect().scale(4);
	return true;
}

const char* MutoidMan::staticTypeName(){
	return "mutoidMan";
}
const char* MutoidMan::getTypeName()const {
	return staticTypeName();
}

const Rect& MutoidMan::getRect() const {
	return m_sprite.getRect().scale(0.8f);
}

void MutoidMan::setPos(const Vec2f& pos){
	m_sprite.setPos(pos);
}

void MutoidMan::damaged(){
	m_health--;
	shoot();//shoots you when you damage him
	//load damaged animation
	if (m_health <= 66){
		if (m_health <= 33){
			m_sprite.loadAnimation(m_pss3, 1, 1, m_damagedAnimation);
		}
		else {
			m_sprite.loadAnimation(m_pss2, 1, 1, m_damagedAnimation);
		}
	}
	else {
		m_sprite.loadAnimation(m_pss1, 1, 1, m_damagedAnimation);
	}
}

void MutoidMan::checkOffScreen(){
	float maxX = TheScreen::Instance()->getSize().x - 210.0f;//minus width
	float maxY = TheScreen::Instance()->getSize().y - 207.0f;//minus height

	if (m_sprite.getPos().x <= 0 + 50){
		m_sprite.setVel(Vec2f(100, 0));
	}
	if (m_sprite.getPos().x >= maxX - 50){
		m_sprite.setVel(Vec2f(-100, 0));
	}
	if (m_sprite.getPos().y <= 0 + 60){
		m_sprite.setVel(Vec2f(0, 100));
	}
	if (m_sprite.getPos().y >= maxY - 30){
		m_sprite.setVel(Vec2f(0, -100));
	}
}

void MutoidMan::shoot(){
	Bullet* bullet = dynamic_cast<Bullet*> (TheGameObjectFactory::Instance()->create(EnemyBullet::staticTypeName()));

	Player* p = ThePlayer::Instance();
	float directionX = p->getPos().x - m_sprite.getPos().x;
	float directionY = p->getPos().y - m_sprite.getPos().y;
	float length = sqrt(directionX*directionX + directionY*directionY);
	float normLength = 1 / length;
	directionX *= normLength;
	directionY *= normLength;
	bullet->setVel(Vec2f(directionX*220.0f, directionY*220.0f));
	//shoot to the position of the player
	bullet->setPos(Vec2f(m_sprite.getPos().x + 50, m_sprite.getPos().y + 50));
	bullet->load();
	static int bulletId = 99999999;
	TheGame::Instance()->addGameObject(bulletId, bullet);
	bulletId--;
}