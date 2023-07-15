#include "Invincible.h"
#include "SpriteSheet.h"
#include "Player.h"
#include "Game.h"
#include "EventPoller.h"
#include "GameObjectFactory.h"
#include "File.h"
#include "Player.h"

GameObject* createInvincible(){
	return new Invincible;
}
static int n = TheGameObjectFactory::Instance()->add(Invincible::staticTypeName(), createInvincible);

void collidePlayerInvincible(GameObject* go1, GameObject* go2){
	Player* p = dynamic_cast<Player*>(go1);
	assert(p);
	Invincible* inv = dynamic_cast<Invincible*>(go2);
	assert(inv);
	inv->RemoveMe();
	p->becomeInvincible();
}
static bool b2 = TheGame::Instance()->addCollisionHandler(Player::staticTypeName(), Invincible::staticTypeName(), collidePlayerInvincible);

bool Invincible::load(File* file){
	static SpriteSheet ssInvincible;
	static bool loaded = false;
	if (!loaded){
		ssInvincible = SpriteSheet(Vec2i(1, 1));
		if (!ssInvincible.load("invincible.png")){
			return false;
		}
		loaded = true;
	}
	m_sprite.setSpriteSheet(&ssInvincible);
	m_sprite.loadAnimation(&ssInvincible, 0, 0, 1);
	m_duration = 5.0f;
	m_timeRemaining = m_duration;

	return true;
}

const char* Invincible::staticTypeName(){
	return "invincible";
}
const char* Invincible::getTypeName()const {
	return staticTypeName();
}