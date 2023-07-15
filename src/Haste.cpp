#include "Haste.h"
#include "SpriteSheet.h"
#include "Player.h"
#include "Game.h"
#include "EventPoller.h"
#include "GameObjectFactory.h"

GameObject* createHaste(){
	return new Haste;
}
static int n = TheGameObjectFactory::Instance()->add(Haste::staticTypeName(), createHaste);

void collidePlayerHaste(GameObject* go1, GameObject* go2){
	Player* p = dynamic_cast<Player*>(go1);
	assert(p);
	Haste* haste = dynamic_cast<Haste*>(go2);
	assert(haste);
	haste->RemoveMe();
	p->increaseSpeed();
}
static bool b2 = TheGame::Instance()->addCollisionHandler(Player::staticTypeName(), Haste::staticTypeName(), collidePlayerHaste);

bool Haste::load(File* file){
	static SpriteSheet ssHaste;
	static bool loaded = false;
	if (!loaded){
		ssHaste = SpriteSheet(Vec2i(1, 1));
		if (!ssHaste.load("haste.png")){
			return false;
		}
		loaded = true;
	}
	m_sprite.setSpriteSheet(&ssHaste);
	m_sprite.loadAnimation(&ssHaste, 0, 0, 1);
	m_duration = 5.0f;
	m_timeRemaining = m_duration;

	return true;
}

const char* Haste::staticTypeName(){
	return "haste";
}
const char* Haste::getTypeName()const {
	return staticTypeName();
}