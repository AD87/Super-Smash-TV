#include "Bazooka.h"
#include "SpriteSheet.h"
#include "Player.h"
#include "Game.h"
#include "EventPoller.h"
#include "GameObjectFactory.h"
#include "File.h"
#include "Player.h"
#include "Timer.h"

GameObject* createBazooka(){
	return new Bazooka;
}
static int n = TheGameObjectFactory::Instance()->add(Bazooka::staticTypeName(), createBazooka);

void collidePlayerBazooka(GameObject* go1, GameObject* go2){
	Player* p = dynamic_cast<Player*>(go1);
	assert(p);
	Bazooka* baz = dynamic_cast<Bazooka*>(go2);
	assert(baz);
	baz->RemoveMe();
	ThePlayer::Instance()->equipBazooka();
}
static bool b2 = TheGame::Instance()->addCollisionHandler(Player::staticTypeName(), Bazooka::staticTypeName(), collidePlayerBazooka);

bool Bazooka::load(File* file){
	static SpriteSheet ssBazooka;
	static bool loaded = false;
	if (!loaded){
		ssBazooka = SpriteSheet(Vec2i(1, 1));
		if (!ssBazooka.load("bazooka.png")){
			return false;
		}
		loaded = true;
	}
	m_sprite.setSpriteSheet(&ssBazooka);
	m_sprite.loadAnimation(&ssBazooka, 0, 0, 1);
	m_duration = 5.0f;
	m_timeRemaining = m_duration;

	return true;
}

const char* Bazooka::staticTypeName(){
	return "bazooka";
}
const char* Bazooka::getTypeName()const {
	return staticTypeName();
}