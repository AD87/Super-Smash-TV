#include "Player.h"
#include "GameObjectFactory.h"
#include "Game.h"
#include "SimpleBullet.h"
#include "bazookaBullet.h"
#include "SoundManager.h"
#include "Timer.h"

Player::~Player(){
	TheGame::Instance()->deleteGameObjectFromMap(1);
}

bool Player::load(File*){
	m_playerSpriteSheet = SpriteSheet(Vec2i(5, 4));
	static bool loadedOk = m_playerSpriteSheet.load("zelda.png");
	assert(loadedOk);	

	if (!m_invincibleImage.load("invincibleCircle.png")){
		return false;
	}
	if (!m_invincibleFinishingImage.load("invincibleCircleFinishing.png")){
		return false;
	}
	if (!TheSoundManager::Instance()->load("shoot.wav")){
		return false;
	}
	if (!TheSoundManager::Instance()->load("bazooka.wav")){
		return false;
	}

	init();

	TheGame::Instance()->addGameObject(1, this);
	return true;
}

const char* Player::staticTypeName(){
	return "player";
}

const char* Player::getTypeName()const{
	return staticTypeName();
}

const Rect& Player::getRect() const{
	return m_sprite.getRect().scale(0.8f);
}

void Player::setPos(const Vec2f& pos){
	m_sprite.setPos(pos);
}

void Player::setVel(const Vec2f& vel){
	m_sprite.setVel(vel);
}

const Vec2f& Player::getPos()const{
	return m_sprite.getPos();
}

float Player::getW()const{
	return m_playerSpriteSheet.getCellW();
}

float Player::getH()const{
	return m_playerSpriteSheet.getCellH();
}

void Player::OnKeyboardEvent(const SDL_KeyboardEvent& ke){
	static int lastKey = 0;//1=left, 2=right, 3=up, 4=down

	if (ke.state == SDL_PRESSED){
		//movement direction
		if (ke.keysym.sym == SDLK_LEFT){
			m_left = true;
			if (lastKey != 1) m_sprite.loadAnimation(&m_playerSpriteSheet, 0, 4, 0.7f);
			lastKey = 1;
		}
		if (ke.keysym.sym == SDLK_RIGHT){
			m_right = true;
			if (lastKey != 2) m_sprite.loadAnimation(&m_playerSpriteSheet, 5, 9, 0.7f);
			lastKey = 2;
		}
		if (ke.keysym.sym == SDLK_UP){
			m_up = true;
			if (lastKey != 3) m_sprite.loadAnimation(&m_playerSpriteSheet, 10, 14, 0.7f);
			lastKey = 3;
		}
		if (ke.keysym.sym == SDLK_DOWN){
			m_down = true;
			if (lastKey != 4) m_sprite.loadAnimation(&m_playerSpriteSheet, 15, 19, 0.7f);
			lastKey = 4;
		}
		//shooting direction
		if (ke.keysym.sym == SDLK_a){
			m_shootLeft = true;
			if (lastKey != 1) m_sprite.loadAnimation(&m_playerSpriteSheet, 0, 4, 0.7f);
		}
		if (ke.keysym.sym == SDLK_d){
			m_shootRight = true;
			if (lastKey != 2) m_sprite.loadAnimation(&m_playerSpriteSheet, 5, 9, 0.7f);
		}
		if (ke.keysym.sym == SDLK_w){
			m_shootUp = true;
			if (lastKey != 3) m_sprite.loadAnimation(&m_playerSpriteSheet, 10, 14, 0.7f);
		}
		if (ke.keysym.sym == SDLK_s){
			m_shootDown = true;
			if (lastKey != 4) m_sprite.loadAnimation(&m_playerSpriteSheet, 15, 19, 0.7f);
		}

	}
	else if (ke.state == SDL_RELEASED){
		if (ke.keysym.sym == SDLK_LEFT) m_left = false;
		else if (ke.keysym.sym == SDLK_RIGHT) m_right = false;
		else if (ke.keysym.sym == SDLK_UP) m_up = false;
		else if (ke.keysym.sym == SDLK_DOWN) m_down = false;
		else if (ke.keysym.sym == SDLK_a) m_shootLeft = false;
		else if (ke.keysym.sym == SDLK_d) m_shootRight = false;
		else if (ke.keysym.sym == SDLK_w) m_shootUp = false;
		else if (ke.keysym.sym == SDLK_s) m_shootDown = false;
	}

	if (!m_left && !m_right && !m_up && !m_down){
		setVel(Vec2f(0, 0));
		stopAnimation();
		lastKey = 0;
	}
}

void Player::update(){
	m_sprite.update();
	
	if (m_justShooted){
		m_shootCooldownRemaining -= TheTimer::Instance()->GetDt();
		if (m_shootCooldownRemaining <= 0){
			m_shootCooldownRemaining = m_shootCooldown;
			m_justShooted = false;//cooldown for shooting
		}
	}

	removePowerUps();
	checkMoving();
	checkShooting();
}

void Player::draw(){
	if (isInvincible()){
		m_invincibleImage.draw(Vec2f(getPos().x - 22, getPos().y + 10));
	}
	if (m_invincibleTimeRemaining < 1.5f){//invincible circle becomes red when is about to finish
		m_invincibleFinishingImage.draw(Vec2f(getPos().x - 22, getPos().y + 10));
	}
	m_sprite.draw();
}

void Player::stopAnimation(){
	m_sprite.loadAnimation(&m_playerSpriteSheet, m_sprite.getCurrentCell(), m_sprite.getCurrentCell(), 0);//stop the animation where it was left
}

void Player::shoot(const Vec2f& bulletVel){
	if (m_shootCooldownRemaining < m_shootCooldown) return;
	m_justShooted = true;

	Bullet* bullet = nullptr;
	static int bulletId = 999999999;
	if (m_bulletType == 1){
		TheSoundManager::Instance()->playSound("shoot.wav");
		bullet = dynamic_cast<Bullet*> (TheGameObjectFactory::Instance()->create(SimpleBullet::staticTypeName()));
		bullet->setVel(bulletVel);
	}
	else if (m_bulletType == 2){
		TheSoundManager::Instance()->playSound("bazooka.wav");
		bullet = dynamic_cast<Bullet*> (TheGameObjectFactory::Instance()->create(BazookaBullet::staticTypeName()));
		bullet->setVel(bulletVel * 1.4f);
	}
	bullet->setPos(Vec2f(m_sprite.getPos().x + getW() / 2, m_sprite.getPos().y + getH() / 2));
	bullet->load();
	TheGame::Instance()->addGameObject(bulletId, bullet);
	bulletId--;
}

void Player::increaseSpeed(){
	m_speed = 350;
	m_speedTimeRemaining = m_speedDuration;//if we collect a powerUp while the same powerUp is active it goes back to full duration
}

void Player::equipBazooka(){
	m_bulletType = 2;
	m_weaponTimeRemaining = m_weaponDuration;
}

void Player::becomeInvincible(){
	m_invincible = true;
	m_invincibleTimeRemaining = m_invincibleDuration;
}

bool Player::isInvincible()const{
	return m_invincible;
}

void Player::checkOffScreen(){
	float maxX = TheScreen::Instance()->getSize().x - getW();
	float maxY = TheScreen::Instance()->getSize().y - getH();

	if (getPos().x <= 0 + 50){
		setPos(Vec2f(0 + 50, getPos().y));
	}
	if (getPos().x >= maxX - 50){
		setPos(Vec2f(maxX - 50, getPos().y));
	}
	if (getPos().y <= 0 + 60){
		setPos(Vec2f(getPos().x, 0 + 60));
	}
	if (getPos().y >= maxY - 30){
		setPos(Vec2f(getPos().x, maxY - 30));
	}
}

void Player::removePowerUps(){//each powerUp only last for a short period of time
	if (m_speed != 240){
		m_speedTimeRemaining -= TheTimer::Instance()->GetDt();
		if (m_speedTimeRemaining <= 0){
			m_speed = 240;
			m_speedTimeRemaining = m_speedDuration;
		}
	}
	if (m_bulletType != 1){
		m_weaponTimeRemaining -= TheTimer::Instance()->GetDt();
		if (m_weaponTimeRemaining <= 0){
			m_bulletType = 1;
			m_weaponTimeRemaining = m_weaponDuration;
		}
	}
	if (isInvincible()){
		m_invincibleTimeRemaining -= TheTimer::Instance()->GetDt();
		if (m_invincibleTimeRemaining <= 0){
			m_invincible = false;
			m_invincibleTimeRemaining = m_invincibleDuration;
		}
	}
}

void Player::checkMoving(){
	if (m_left) setVel(Vec2f(-m_speed, 0));
	if (m_right) setVel(Vec2f(m_speed, 0));
	if (m_up) setVel(Vec2f(0, -m_speed));
	if (m_down) setVel(Vec2f(0, m_speed));

	float diagonalVel = m_speed * 0.7f;
	if (m_up && m_right){
		setVel(Vec2f(diagonalVel, -diagonalVel));
	}
	if (m_right && m_down){
		setVel(Vec2f(diagonalVel, diagonalVel));
	}
	if (m_down && m_left){
		setVel(Vec2f(-diagonalVel, diagonalVel));
	}
	if (m_left && m_up){
		setVel(Vec2f(-diagonalVel, -diagonalVel));
	}
}

void Player::checkShooting(){
	if (m_shootLeft) shoot(Vec2f(-500, 0));
	else if (m_shootRight) shoot(Vec2f(500, 0));
	else if (m_shootUp) shoot(Vec2f(0, -500));
	else if (m_shootDown) shoot(Vec2f(0, 500));
}

void Player::init(){
	m_sprite.loadAnimation(&m_playerSpriteSheet, 0, 0, 1);

	setPos(Vec2f(470, 340));
	setVel(Vec2f(0, 0));
	m_isAlive = true;
	m_speed = 240;
	m_bulletType = 1;
	m_invincible = false;
	m_justShooted = false;
	setisAlive(true);

	m_left = false;
	m_right = false;
	m_up = false;
	m_down = false;
	m_shootLeft = false;
	m_shootRight = false;
	m_shootUp = false;
	m_shootDown = false;

	m_speedDuration = 5.0f;
	m_speedTimeRemaining = m_speedDuration;
	m_weaponDuration = 5.0f;
	m_weaponTimeRemaining = m_weaponDuration;
	m_invincibleDuration = 5.0f;
	m_invincibleTimeRemaining = m_invincibleDuration;
	m_shootCooldown = .18f;
	m_shootCooldownRemaining = m_shootCooldown;
}

void Player::setisAlive(bool b){
	m_isAlive = b;
}

bool Player::getIsAlive()const{
	return m_isAlive;
}