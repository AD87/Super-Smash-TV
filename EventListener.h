#pragma once
#include <SDL.h>

class EventListener{
public:
	virtual ~EventListener(){}

	void HandleEvent(const SDL_Event& event);

	virtual void OnQuit(){}
	virtual void OnKeyboardEvent(const SDL_KeyboardEvent&){}
	virtual void OnMouseEvent(const SDL_MouseMotionEvent&){}
	virtual void OnJoystickAxisEvent(const SDL_JoyAxisEvent&){}
};