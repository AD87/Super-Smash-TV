#include <functional>
#include "HighScoresState.h"
#include "EventPoller.h"
#include "SoundManager.h"
#include "File.h"
#include "PlayState.h"
#include "MainMenuState.h"
#include "Game.h"

bool HighScoresState::load(const std::string& fileName){
	TheEventPoller::Instance()->addHandler(this);

	if (!m_bg.load("scoresState.gif")){
		return false;
	}
	m_font.load("ARDESTINE.ttf", 40);

	File f;
	if (!f.openRead(fileName)){
		f.reportError("Failed to open file");
		return false;
	}
	int line;
	while (f.getInt(&line)){
		m_scores.push_back(line);
	}
	std::sort(m_scores.begin(), m_scores.end(), std::greater<int>());//sort in descending order
	return true;
}

void HighScoresState::update(){

}

void HighScoresState::draw(){
	if (m_drawOnce == true) return;
	m_bg.draw(Vec2f(0, 0));
	m_font.draw(465, 560, std::to_string(ThePlayState::Instance()->getScore()), SDL_Color{ 220, 130, 5, 0 });
	printScores();
	m_drawOnce = true;
}

void HighScoresState::onActive(){
	assert(load("highScores.txt"));
	m_drawOnce = false;
}

void HighScoresState::onDeactivated(){
	TheEventPoller::Instance()->removeHandler(this);
	m_scores.clear();
}

void HighScoresState::OnKeyboardEvent(const SDL_KeyboardEvent& ke){
	if (ke.state == SDL_PRESSED){
		TheGame::Instance()->setState(TheMainMenuState::Instance());
	}
}

void HighScoresState::OnQuit(){
	TheGame::Instance()->quit();
}

void HighScoresState::printScores(){
	int lastElement = 0;
	if (m_scores.size() < 10){
		lastElement = m_scores.size();//in case the highscores contains less than 10 elements
	}
	else {
		lastElement = 10;
	}
	int yPos = 25;
	for (int i = 0; i < lastElement; i++){
		m_font.draw(350, yPos, std::to_string(m_scores[i]), SDL_Color{ 0, 0, 255, 0 });
		yPos += 38;// start with the 1st and move down
	}
}