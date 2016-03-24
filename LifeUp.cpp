#include "LifeUp.h"
#include "GameObject.h"
#include "GameObjectFactory.h"
#include "Player.h"
#include "PlayState.h"
#include "Game.h"

GameObject* createLifeUp(){
	return new LifeUp;
}
static int n = TheGameObjectFactory::Instance()->add(LifeUp::staticTypeName(), createLifeUp);

void collidePlayerLifeUp(GameObject* go1, GameObject* go2){
	Player* p = dynamic_cast<Player*>(go1);
	assert(p);
	LifeUp* life = dynamic_cast<LifeUp*>(go2);
	assert(life);
	life->RemoveMe();
	ThePlayState::Instance()->increaseLives(1);
}
static bool b2 = TheGame::Instance()->addCollisionHandler(Player::staticTypeName(), LifeUp::staticTypeName(), collidePlayerLifeUp);

bool LifeUp::load(File* file){
	static SpriteSheet ssLifeUp;
	static bool loaded = false;
	if (!loaded){
		ssLifeUp = SpriteSheet(Vec2i(1, 1));
		if (!ssLifeUp.load("1up.png")){
			return false;
		}
		loaded = true;
	}
	m_sprite.setSpriteSheet(&ssLifeUp);
	m_sprite.loadAnimation(&ssLifeUp, 0, 0, 1);
	m_duration = 5.0f;
	m_timeRemaining = m_duration;

	return true;
}

const char* LifeUp::staticTypeName(){
	return "lifeUp";
}
const char* LifeUp::getTypeName()const {
	return staticTypeName();
}