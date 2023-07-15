#include "GameObject.h"
#include "Factory.h"
#include "Singleton.h"

typedef Factory<GameObject> GameObjectFactory;

typedef Singleton<GameObjectFactory> TheGameObjectFactory;