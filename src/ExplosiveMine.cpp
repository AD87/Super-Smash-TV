#include "ExplosiveMine.h"
#include "SpriteSheet.h"
#include "Player.h"
#include "Game.h"
#include "EventPoller.h"
#include "GameObjectFactory.h"
#include "PlayState.h"
#include "File.h"

GameObject* createExplosiveMine(){
	return new ExplosiveMine;
}
static int n = TheGameObjectFactory::Instance()->add(ExplosiveMine::staticTypeName(), createExplosiveMine);

void collidePlayerExplosiveMine(GameObject* go1, GameObject* go2){
	Player* p = dynamic_cast<Player*>(go1);
	assert(p);
	ExplosiveMine* mine = dynamic_cast<ExplosiveMine*>(go2);
	assert(mine);
	mine->RemoveMe();
	if (!ThePlayer::Instance()->isInvincible()){
		ThePlayState::Instance()->decreaseLive();
	}
}
static bool b2 = TheGame::Instance()->addCollisionHandler(Player::staticTypeName(), ExplosiveMine::staticTypeName(), collidePlayerExplosiveMine);

void ExplosiveMine::draw(){
	m_sprite.draw();
}
void ExplosiveMine::update(){
	m_sprite.update();
}
bool ExplosiveMine::load(File* file){
	static SpriteSheet ssMine;
	static bool loaded = false;
	if (!loaded){
		ssMine = SpriteSheet(Vec2i(1, 1));
		if (!ssMine.load("mine.png")){
			return false;
		}
		loaded = true;
	}
	m_sprite.setSpriteSheet(&ssMine);

	float fx;
	if (!file->getFloat(&fx)){
	return false;
	}
	float fy;
	if (!file->getFloat(&fy)){
	return false;
	}
	m_sprite.setPos(Vec2f(fx, fy));

	m_sprite.loadAnimation(&ssMine, 0, 0, 1);

	return true;
}

const char* ExplosiveMine::staticTypeName(){
	return "explosiveMine";
}
const char* ExplosiveMine::getTypeName()const {
	return staticTypeName();
}

const Rect& ExplosiveMine::getRect() const {
	return m_sprite.getRect();
}

void ExplosiveMine::setPos(const Vec2f& pos){
	m_sprite.setPos(pos);
}