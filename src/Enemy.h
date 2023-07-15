#pragma once
#include <set>
#include "GameObject.h"
#include "Sprite.h"

class Enemy : public GameObject{
public:
	Enemy();
	virtual ~Enemy();
	void setPos(const Vec2f& pos);
	void showBlood();

	static void killAllEnemies();
protected:
	static void addToEnemySet(Enemy* e);
	static void removeFromEnemySet(Enemy* e);

	Sprite m_sprite;
	typedef std::set<Enemy*> EnemySet;
	static EnemySet m_allEnemies;
};