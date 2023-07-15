#include <math.h>
#include "PlayState.h"
#include "EventPoller.h"
#include "Screen.h"
#include "BatEnemy.h"
#include "SoundManager.h"
#include "Game.h"
#include "HighScoresState.h"
#include "Timer.h"
#include "GameObjectFactory.h"
#include "PowerUp.h"
#include "killAll.h"
#include "Haste.h"
#include "Bazooka.h"
#include "LifeUp.h"
#include "Invincible.h"
#include "File.h"
#include "RandomGenerator.h"

bool PlayState::load(){
	static bool loaded = false;
	if (loaded)return true;//all  the images and sounds will get loaded once only, even if we come back to the state
	
	assert(ThePlayer::Instance()->load(nullptr));

	m_font.load("ARDESTINE.ttf", 40);

	if (!m_bg.load("bg.png")){
		return false;
	}
	if (!TheSoundManager::Instance()->load("scream.wav")){
		return false;
	}
	m_ssLevelCleared = SpriteSheet(Vec2i(1, 1));
	if (!m_ssLevelCleared.load("levelCleared.png")){
		return false;
	}
	m_levelCleared.setPos(Vec2f(230, 180));
	m_levelCleared.setSpriteSheet(&m_ssLevelCleared);
	m_levelClearedDuration = 3.0f;
	m_levelClearedTimeRemaining = m_levelClearedDuration;

	loaded = true;
	return true;
}

void PlayState::draw() {
	m_bg.draw(Vec2f(0, 0));
	SDL_Color colour = { 0, 0, 255, 0 };
	m_font.draw(80, 115, std::to_string(m_score), colour );
	m_font.draw(67, 63, std::to_string(m_lives), colour );
	if (!m_isLoading && ThePlayer::Instance()->getIsAlive()){
		TheGame::Instance()->drawGameObject();
	}
	else if (!ThePlayer::Instance()->getIsAlive()){
		SDL_Color colour = { 255, 0, 255, 0 };
		m_font.draw(375, 330, "GAME OVER", colour);
		m_font.draw(180, 400, "Press Return to see the scores", colour);
		m_font.draw(300, 440, "Press Escape to quit", colour);
	}
}

void PlayState::update(){
	if (!ThePlayer::Instance()->getIsAlive() && !m_gameOverOnce){
		gameOver();
		m_gameOverOnce = true;
	}
	if (!m_isLoading && ThePlayer::Instance()->getIsAlive()){
		TheGame::Instance()->updateGameObject();
		generateEnemies();
		generatePowerUps();
		ThePlayer::Instance()->checkOffScreen();
	}
	if (m_score >= m_scoreForNextLevel){//when we reach a certain amount of points we go to the next level
		m_isLoading = true;

		endLevel();
		m_levelCleared.draw();
		m_levelClearedTimeRemaining -= TheTimer::Instance()->GetDt();
		if (m_levelClearedTimeRemaining <= 0){
			loadLevel(m_nextLevelFileName);
			m_levelClearedTimeRemaining = m_levelClearedDuration;
			m_isLoading = false;
		}
	}
}

void PlayState::generateEnemies(){
	RandomGenerator* rGen = TheRandomGenerator::Instance();
	if (rGen->checkGenerateEnemies()){
		int door = rGen->whichDoor();
		int numberOfEnemies = rGen->numberOfEnemies();
		for (int i = 0; i < numberOfEnemies; i++){
			BatEnemy* batEnemy = dynamic_cast<BatEnemy*> (TheGameObjectFactory::Instance()->create(BatEnemy::staticTypeName()));
			batEnemy->setPos(rGen->randomPositionBatEnemy(door));
			batEnemy->load();
			static int batEnemyId = 99999;
			TheGame::Instance()->addGameObject(batEnemyId, batEnemy);
			batEnemyId--;
		}
	}
}

void PlayState::generatePowerUps(){
	RandomGenerator* rGen = TheRandomGenerator::Instance();
	if (rGen->checkGeneratePowerUps()){
		PowerUp* pUp = nullptr;
		int randomPowerUp = rGen->randomPowerUp();
		if (randomPowerUp == 1){
			pUp = dynamic_cast<KillAll*> (TheGameObjectFactory::Instance()->create(KillAll::staticTypeName()));
		}
		else if (randomPowerUp == 2){
			pUp = dynamic_cast<Haste*> (TheGameObjectFactory::Instance()->create(Haste::staticTypeName()));
		}
		else if (randomPowerUp == 3){
			pUp = dynamic_cast<Bazooka*> (TheGameObjectFactory::Instance()->create(Bazooka::staticTypeName()));
		}
		else if (randomPowerUp == 4){
			pUp = dynamic_cast<Invincible*> (TheGameObjectFactory::Instance()->create(Invincible::staticTypeName()));
		}
		else if (randomPowerUp == 5){
			pUp = dynamic_cast<LifeUp*> (TheGameObjectFactory::Instance()->create(LifeUp::staticTypeName()));
		}
		pUp->setPos(rGen->powerUpPosition());
		pUp->load();
		static int powerUpId = 9999;
		TheGame::Instance()->addGameObject(powerUpId, pUp);
		powerUpId--;
	}
}

void PlayState::incrementScore(int points){
	m_score += points;
}

void PlayState::decreaseLive(){
	TheSoundManager::Instance()->playSound("scream.wav");
	if (m_lives == 0){
		ThePlayer::Instance()->setisAlive(false);
	}
	else {
		m_lives--;
		Player* player = ThePlayer::Instance();
		player->setPos(Vec2f(470, 340));
		player->becomeInvincible();
	}
}

void PlayState::increaseLives(int howMany){
	m_lives += howMany;
}

void PlayState::writeScoreToFile(){
	std::ofstream file("highScores.txt",std::ios::app);

	if (!file.is_open()){
		//error
	}

	file << m_score << std::endl;
	file.close();
}

int PlayState::getScore(){
	return m_score;
}

void PlayState::onActive(){
	assert(load());
	assert(loadLevel("level1.txt"));
	ThePlayer::Instance()->init();
	m_isLoading = false;
	m_score = 0;
	m_lives = 3;
	m_gameOverOnce = false;

	TheEventPoller::Instance()->addHandler(ThePlayer::Instance());
}

void PlayState::onDeactivated(){
	TheEventPoller::Instance()->removeHandler(this);
}

void PlayState::OnKeyboardEvent(const SDL_KeyboardEvent& ke){
	if (ke.state == SDL_PRESSED){
		if (ke.keysym.sym == SDLK_RETURN){
			TheGame::Instance()->setState(TheHighScoresState::Instance());
		}
		if (ke.keysym.sym == SDLK_ESCAPE){
			TheGame::Instance()->quit();
		}
	}
}

void PlayState::OnQuit(){
	TheGame::Instance()->quit();
}

void PlayState::endLevel(){
	deleteAllGameObjects();
	ThePlayer::Instance()->setPos(Vec2f(470, 340));
	m_levelCleared.loadAnimation(&m_ssLevelCleared, 0, 0, m_levelClearedDuration);
}

bool PlayState::loadLevel(const std::string& fileName){
	File f;
	if (!f.openRead(fileName)){
		f.reportError("Failed to open file");
		return false;
	}

	if (!f.getInt(&m_scoreForNextLevel)){//score to pass to next level
		f.reportError("Expected score");
		return false;
	}
	if (!f.getString(&m_nextLevelFileName)){//next level file name
		f.reportError("Expected next level file name");
		return false;
	}

	std::string line;
	while (f.getString(&line)){
		GameObject* go = TheGameObjectFactory::Instance()->create(line);
		if (!go){
			f.reportError("Failed to create an object of " + line + "type");
			return false;
		}

		int id = -1;
		if (!f.getInt(&id)){
			f.reportError("Expected ID for " + line);
			return false;
		}

		if (!go->load(&f)){
			f.reportError("Failed to load in data members of an object");
			return false;
		}

		if (!TheGame::Instance()->addGameObject(id, go)){
			f.reportError("Duplicate ID " + std::to_string(id));
			return false;
		}
	}
	return true;
}

void PlayState::gameOver(){
	deleteAllGameObjects();
	TheEventPoller::Instance()->removeHandler(ThePlayer::Instance());
	writeScoreToFile();
	TheEventPoller::Instance()->addHandler(this);
}

void PlayState::deleteAllGameObjects(){
	GameObjectMap* allGameObjects = TheGame::Instance()->getAllGameObjects();
	for (GameObjectMap::iterator it = allGameObjects->begin(); it != allGameObjects->end(); ++it){
		if (it->second->getTypeName() != Player::staticTypeName()){//make sure we dont delete the player
			it->second->RemoveMe();
		}
	}
	TheGame::Instance()->updateGameObject();
}
