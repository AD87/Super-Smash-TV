#pragma once
#include <iostream>
#include <assert.h>
#include "Sprite.h"
#include "EventListener.h"
#include "SpriteSheet.h"
#include "GameObject.h"
#include "Singleton.h"


class Player :public EventListener, public GameObject, public Uncopyable{
private:
	Player(){}
	friend Singleton<Player>;
public:
	~Player();
	bool load(File*) override;
	void update() override;
	void draw() override;
	static const char* staticTypeName();
	const char* getTypeName()const override;
	const Rect& getRect() const override;

	void OnKeyboardEvent(const SDL_KeyboardEvent& ke)override;

	void stopAnimation();
	void shoot(const Vec2f& bulletVel);
	void increaseSpeed();
	void equipBazooka();
	void becomeInvincible();

	bool isInvincible()const;
	void checkOffScreen();
	void removePowerUps();
	void checkMoving();
	void checkShooting();
	void init();

	void setisAlive(bool b);
	bool getIsAlive()const;

	void setPos(const Vec2f& pos);
	void setVel(const Vec2f& vel);
	const Vec2f& getPos()const;
	float getW()const;
	float getH()const;
	
private:
	Sprite m_sprite;
	SpriteSheet m_playerSpriteSheet;

	bool m_isAlive;
	float m_speed;
	int m_bulletType;
	bool m_invincible;
	Image m_invincibleImage;
	Image m_invincibleFinishingImage;
	float m_speedDuration;
	float m_speedTimeRemaining;
	float m_weaponDuration;
	float m_weaponTimeRemaining;
	float m_invincibleDuration;
	float m_invincibleTimeRemaining;
	bool m_justShooted;
	float m_shootCooldown;
	float m_shootCooldownRemaining;

	bool m_left = false;
	bool m_right = false;
	bool m_up = false;
	bool m_down = false;
	bool m_shootLeft = false;
	bool m_shootRight = false;
	bool m_shootUp = false;
	bool m_shootDown = false;
};

typedef Singleton<Player> ThePlayer;