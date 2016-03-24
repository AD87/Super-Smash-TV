#include"EventPoller.h"
#include"EventListener.h"

void EventPoller::update(){
	//make copy of container listeners, in case we manipulate the elements in the container
	Listeners listenerCopy = m_listeners;
	//get each event
	SDL_Event event;
	while (SDL_PollEvent(&event)){
		//inner loop
		for (auto it = listenerCopy.begin(); it != listenerCopy.end(); ++it){
			EventListener* eh = *it;
			eh->HandleEvent(event);
		}
	}
}

void EventPoller::addHandler(EventListener* eh){

	m_listeners.insert(eh);
}

void EventPoller::removeHandler(EventListener* eh){
	m_listeners.erase(eh);
}