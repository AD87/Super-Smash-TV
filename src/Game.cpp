#include <cassert>
#include "Game.h"
#include "Timer.h"
#include "EventPoller.h"
#include "SimpleCollisionSystem.h"
#include "Player.h"

Game::Game(){
	m_state = nullptr;
	m_collisionSystem = new SimpleCollisionSystem;
}

Game::~Game(){
	delete m_collisionSystem;
}

void Game::run(){
	while (!m_quit){
		draw();
		update();
		TheScreen::Instance()->flipBuffer();
	}
}

void Game::draw(){
	assert(m_state);
	m_state->draw();
}

void Game::update(){
	TheTimer::Instance()->Update();
	TheEventPoller::Instance()->update();
	assert(m_state);
	m_state->update();
	m_collisionSystem->checkCollisions(&m_gameObjects);
}

void Game::quit(){
	m_quit = true;
}

void Game::drawGameObject(){
	for (GameObjectMap::iterator it = m_gameObjects.begin(); it != m_gameObjects.end();++it){
		GameObject* go = it->second;
		go->draw();
	}
}

void Game::updateGameObject(){
	for (GameObjectMap::iterator it = m_gameObjects.begin(); it != m_gameObjects.end(); ){
		GameObject* go = it->second;
		go->update();
		if (it->second->getRemoveMe()){
			delete it->second;
			it = m_gameObjects.erase(it);
			
		}
		else
		{
			++it;
		}
	}
}

bool Game::addGameObject(int id, GameObject* go){
	if (m_gameObjects.find(id) != m_gameObjects.end()){
		return false;
	}

	m_gameObjects[id] = go;
	return true;
}

GameObjectMap* Game::getAllGameObjects(){
	return &m_gameObjects;
}

void Game::deleteGameObjectFromMap(int id){
	m_gameObjects.erase(id);
}

void Game::handleCollision(GameObject* go1, GameObject* go2){
	typePair key(go1->getTypeName(), go2->getTypeName());
	collisionMap::iterator it = m_collisionMap.find(key);
	if (it != m_collisionMap.end()){
		collisionHandlerFunction chf = it->second;
		assert(chf);
		chf(go1, go2);
	}
	else {
		std::swap(key.first, key.second);
		collisionMap::iterator it = m_collisionMap.find(key);
		if (it != m_collisionMap.end()){
			collisionHandlerFunction chf = it->second;
			assert(chf);
			chf(go2, go1);//swap the game objects
		}
	}
}

bool Game::addCollisionHandler(const char* typeName1, const char* typeName2, collisionHandlerFunction func){
	typePair key(typeName1, typeName2);
	assert(m_collisionMap.find(key) == m_collisionMap.end());
	m_collisionMap[key] = func;
	return true;
}

void Game::setState(GameState* state){
	if (m_state == state)return;
	if (m_state) m_state->onDeactivated();
	m_state = state;
	m_state->onActive();
}

const GameState& Game::getState() const{
	return *m_state;
}
