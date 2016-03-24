#include "killAll.h"
#include "SpriteSheet.h"
#include "Player.h"
#include "Game.h"
#include "EventPoller.h"
#include "GameObjectFactory.h"
#include "SoundManager.h"
#include "File.h"
#include "Enemy.h"

GameObject* createKillAll(){
	return new KillAll;
}
static int n = TheGameObjectFactory::Instance()->add(KillAll::staticTypeName(), createKillAll);

void collidePlayerKillAll(GameObject* go1, GameObject* go2){
	Player* p = dynamic_cast<Player*>(go1);
	assert(p);
	KillAll* ka = dynamic_cast<KillAll*>(go2);
	assert(ka);
	ka->RemoveMe();
	Enemy::killAllEnemies();
	TheSoundManager::Instance()->playSound("bingo.wav");
}
static bool b2 = TheGame::Instance()->addCollisionHandler(Player::staticTypeName(), KillAll::staticTypeName(), collidePlayerKillAll);

bool KillAll::load(File* file){
	static SpriteSheet ssKillAll;
	static bool loaded = false;
	if (!loaded){
		ssKillAll = SpriteSheet(Vec2i(1, 1));
		if (!ssKillAll.load("killAll.png")){
			return false;
		}
		if (!TheSoundManager::Instance()->load("bingo.wav")){
			return false;
		}
		loaded = true;
	}
	m_sprite.setSpriteSheet(&ssKillAll);
	m_sprite.loadAnimation(&ssKillAll, 0, 0, 1);
	m_duration = 5.0f;
	m_timeRemaining = m_duration;

	return true;
}

const char* KillAll::staticTypeName(){
	return "killAll";
}
const char* KillAll::getTypeName()const {
	return staticTypeName();
}