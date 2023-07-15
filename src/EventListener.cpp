#include "EventListener.h"

void EventListener::HandleEvent(const SDL_Event& event){
	switch (event.type){
	case SDL_QUIT:
		OnQuit();
		break;

	case SDL_KEYDOWN:
		//fall through
	case SDL_KEYUP:
		OnKeyboardEvent(event.key);
		break;

	case SDL_MOUSEMOTION:
		OnMouseEvent(event.motion);
		break;
		
	case SDL_JOYAXISMOTION:
		OnJoystickAxisEvent(event.jaxis);
		break;

	//more event types to be added
	}
}