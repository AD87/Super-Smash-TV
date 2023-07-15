#include "SDL.h"
#include "Screen.h"
#include "Game.h"
#include "MainMenuState.h"

int main(int, char**){
	Screen* theScreen = TheScreen::Instance();
	theScreen->createWindow("myWindow", 970, 635);

	TheGame::Instance()->setState(TheMainMenuState::Instance());

	TheGame::Instance()->run();

	return 0;
}