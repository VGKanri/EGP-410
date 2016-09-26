#pragma once

#include "GameMessage.h"
#include "Vector2D.h"

class Vector2D;

class AddUnitMessageSeek :public GameMessage
{
public:
	AddUnitMessageSeek(Sprite* sprite);
	~AddUnitMessageSeek();

	void process();

private:
	Sprite* mSprite;
}; 
