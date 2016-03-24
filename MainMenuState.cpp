#include "MainMenuState.h"
#include "EventPoller.h"
#include "SoundManager.h"
#include "PlayState.h"
#include "Game.h"

bool MainMenuState::load(){
	static bool loaded = false;
	if (loaded)return true;

	TheSoundManager::Instance()->playMusic("Smash_TV.wav");

	if (!m_bg.load("menu.png")){
		return false;
	}
	if (!m_helpScreen.load("helpscreen.png")){
		return false;
	}
	if (!TheSoundManager::Instance()->load("intro.wav")){
		return false;
	}
	TheSoundManager::Instance()->playSound("intro.wav");
	m_showHelp = false;
	
	loaded = true;
	return true;
}

void MainMenuState::update(){

}

void MainMenuState::draw(){
	if (m_showHelp == true){
		m_helpScreen.draw(Vec2f(0, 0));
	}
	else m_bg.draw(Vec2f(0, 0));
}

void MainMenuState::onActive(){
	assert(load());
	TheEventPoller::Instance()->addHandler(this);
}

void MainMenuState::onDeactivated(){
	TheEventPoller::Instance()->removeHandler(this);
}

void MainMenuState::OnKeyboardEvent(const SDL_KeyboardEvent& ke){
	if (ke.state == SDL_PRESSED){
		m_showHelp = false;//return to menu after we press any key
		if (ke.keysym.sym == SDLK_RETURN){
			TheGame::Instance()->setState(ThePlayState::Instance());
		}
		else if (ke.keysym.sym == SDLK_h){
			m_showHelp = true;
		}
	}
}

void MainMenuState::OnQuit(){
	TheGame::Instance()->quit();
}