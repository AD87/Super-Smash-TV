#pragma once
#include <set>
#include "Singleton.h"

class EventListener;

class EventPoller: public Uncopyable{
private:
	EventPoller(){}
	friend class Singleton<EventPoller>;
public:
	void update();

	void addHandler(EventListener* eh);
	void removeHandler(EventListener* eh);
private:
	typedef std::set<EventListener*> Listeners;
	Listeners m_listeners;
};

typedef Singleton<EventPoller> TheEventPoller;