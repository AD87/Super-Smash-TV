#include <iostream>
#include "GameObject.h"
#include "Game.h"
#include "SimpleCollisionSystem.h"

bool theyCollide(GameObject* go1, GameObject* go2){
	Rect r1 = go1->getRect();
	Rect r2 = go2->getRect();
	return r1.intersects(r2);
}

void SimpleCollisionSystem::checkCollisions(GameObjectMap* gos){
	for (GameObjectMap::iterator it = gos->begin(); it != gos->end(); ++it){
		std::pair<const int, GameObject*>& p = *it;

		GameObjectMap::iterator jt = it;
		jt++;//we make jt start 1 plus it, so we dont test the objects twice
		for (; jt != gos->end(); ++jt){
			std::pair<const int, GameObject*>& q = *jt;

			//std::cout << "I am testing objects " << p.first << " and " << q.first << std::endl;
			
			GameObject* go1 = p.second;
			GameObject* go2 = q.second;
			std::string s = go1->getTypeName();
			std::string s2 = go2->getTypeName();
			if (theyCollide(go1, go2)){
				//double dispatch
				TheGame::Instance()->handleCollision(go1, go2);
			}
		}
	}
}