#pragma once
#include "PowerUp.h"
#include "Sprite.h"

class Haste : public PowerUp {
public:
	virtual bool load(File* f = nullptr)override;

	static const char* staticTypeName();
	virtual const char* getTypeName()const override;
};