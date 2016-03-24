#pragma once
#include <map>
#include "Rect.h"

class File;

class GameObject{
public:
	GameObject(){
		m_toBeRemoved = false;
	}
	virtual ~GameObject(){}
	virtual void draw() = 0;
	virtual void update() = 0;
	virtual bool load(File* f = nullptr){ return true; }//default implemention in case this function is not overriden

	bool getRemoveMe() const{
		return m_toBeRemoved;
	}
	void RemoveMe(){
		m_toBeRemoved = true;
	}

	virtual const char* getTypeName()const = 0;//const char* instead of string because it will never change

	virtual const Rect& getRect() const = 0;//to be overriden by all game objects, calculating and returning their Rect
protected:
	bool m_toBeRemoved;
};

typedef std::map<int, GameObject*> GameObjectMap;