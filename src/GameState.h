#pragma once
#include "Singleton.h"

class GameState:public Uncopyable{
public:
	virtual ~GameState(){}
	virtual void update() = 0;
	virtual void draw() = 0;

	virtual void onActive(){}
	virtual void onDeactivated(){}
private:
	
};