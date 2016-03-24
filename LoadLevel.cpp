#include "LoadLevel.h"
#include "ReportError.h"
#include "File.h"
#include "Game.h"
#include "GameObject.h"
#include "GameObjectFactory.h"

bool loadLevel(const std::string& fileName){
	File f;
	if (!f.openRead(fileName)){
		f.reportError("Failed to open file");
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