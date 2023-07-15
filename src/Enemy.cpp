#include "Enemy.h"
#include "EnemyBlood.h"
#include "GameObjectFactory.h"
#include "Game.h"
#include "PlayState.h"
#include "BatEnemy.h"
#include "BombEnemy.h"

Enemy::EnemySet Enemy::m_allEnemies;

Enemy::Enemy(){
	addToEnemySet(this);
}

Enemy::~Enemy(){
	removeFromEnemySet(this);
}

void Enemy::setPos(const Vec2f& pos){
	m_sprite.setPos(pos);
}

void Enemy::showBlood(){
	EnemyBlood* blood = dynamic_cast<EnemyBlood*> (TheGameObjectFactory::Instance()->create(EnemyBlood::staticTypeName()));
	blood->load();
	blood->setPos(m_sprite.getPos());
	static int bloodId = 99999999;
	TheGame::Instance()->addGameObject(bloodId, blood);
	bloodId--;
}

void Enemy::killAllEnemies(){
	for (auto it = m_allEnemies.begin(); it != m_allEnemies.end(); ++it){
		(*it)->RemoveMe();
		(*it)->showBlood();
		if (dynamic_cast<BatEnemy*>(*it)){
			ThePlayState::Instance()->incrementScore(1);
		}
		else if (dynamic_cast<BatEnemy*>(*it)){
			ThePlayState::Instance()->incrementScore(3);
		}
	}
}

void Enemy::addToEnemySet(Enemy* e){
	Enemy::m_allEnemies.insert(e);
}

void Enemy::removeFromEnemySet(Enemy* e){
	Enemy::m_allEnemies.erase(e);
}

