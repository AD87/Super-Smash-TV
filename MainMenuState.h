#pragma once
#include "GameState.h"
#include "Image.h"
#include "EventListener.h"

class MainMenuState :public GameState, public EventListener{
private:
	MainMenuState(){}
	friend Singleton<MainMenuState>;
public:
	bool load();
	virtual void update() override;
	virtual void draw() override;
	virtual void onActive()override;
	virtual void onDeactivated()override;
	void OnKeyboardEvent(const SDL_KeyboardEvent& ke)override;
	virtual void OnQuit()override;
private:
	Image m_bg;
	Image m_helpScreen;
	bool m_showHelp;
};

typedef Singleton<MainMenuState> TheMainMenuState;