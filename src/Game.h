#pragma once
#include "GameObject.h"
#include "Singleton.h"
#include "Screen.h"
#include "GameState.h"

class CollisionSystem;

class Game:public Uncopyable{
private:
	Game();
	friend class Singleton<Game>;
public:
	~Game();
	void run();
	void draw();
	void update();

	void quit();

	void drawGameObject();
	void updateGameObject();
	bool addGameObject(int id, GameObject* go);
	GameObjectMap* getAllGameObjects();
	void deleteGameObjectFromMap(int id);

	typedef void(*collisionHandlerFunction)(GameObject* go1, GameObject* go2);//type of function that return void and takes 2 gameObjects
	void handleCollision(GameObject* go1, GameObject* go2);
	bool addCollisionHandler(const char* typeName1, const char* typeName2, collisionHandlerFunction func);
	
	void setState(GameState* state);
	const GameState& getState() const;

private:
	GameState* m_state;
	GameObjectMap m_gameObjects;
	CollisionSystem* m_collisionSystem;
	typedef std::pair<std::string, std::string> typePair;
	typedef std::map<typePair, collisionHandlerFunction> collisionMap;
	collisionMap m_collisionMap;
	bool m_quit;
};

typedef Singleton<Game> TheGame;