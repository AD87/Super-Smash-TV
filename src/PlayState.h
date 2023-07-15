#pragma once
#include <list>
#include "GameState.h"
#include "Singleton.h"
#include "Image.h"
#include "Player.h"
#include "Sprite.h"
#include "Enemy.h"
#include "RandomGenerator.h"
#include "Font.h"

class PlayState :public GameState, public EventListener{
private:
	PlayState(){}
	friend Singleton<PlayState>;
public:
	bool load();
	virtual void update() override;
	virtual void draw() override;

	void generateEnemies();
	void generatePowerUps();
	void incrementScore(int points);
	void decreaseLive();
	void increaseLives(int howMany);
	void writeScoreToFile();
	int getScore();

	virtual void onActive()override;
	virtual void onDeactivated()override;
	void OnKeyboardEvent(const SDL_KeyboardEvent& ke)override;
	virtual void OnQuit()override;

private:
	void endLevel();
	bool loadLevel(const std::string& fileName);//made it game specific
	void gameOver();
	void deleteAllGameObjects();

	bool m_gameOverOnce;

	Image m_bg;
	int m_score;
	int m_lives;
	Font m_font;

	Sprite m_levelCleared;
	SpriteSheet m_ssLevelCleared;
	float m_levelClearedDuration;
	float m_levelClearedTimeRemaining;
	bool m_isLoading;
	int m_scoreForNextLevel;
	std::string m_nextLevelFileName;
};

typedef Singleton<PlayState> ThePlayState;