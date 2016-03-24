#pragma once
#include <vector>
#include "GameState.h"
#include "Image.h"
#include "Font.h"
#include "EventListener.h"

class HighScoresState :public GameState, public EventListener{
private:
	HighScoresState(){}
	friend Singleton<HighScoresState>;
public:
	bool load(const std::string& fileName);
	virtual void update() override;
	virtual void draw() override;
	virtual void onActive()override;
	virtual void onDeactivated()override;
	void OnKeyboardEvent(const SDL_KeyboardEvent& ke)override;
	virtual void OnQuit()override;
private:
	void printScores();

	Image m_bg;
	std::vector<unsigned int> m_scores;
	Font m_font;
	bool m_drawOnce;
};

typedef Singleton<HighScoresState> TheHighScoresState;