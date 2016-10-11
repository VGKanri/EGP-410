#pragma once

#include "GameMessage.h"
#include "Vector2D.h"

class Vector2D;

class AddUnitMessageArrive :public GameMessage
{
public:
	AddUnitMessageArrive(Sprite* sprite);
	~AddUnitMessageArrive();

	void process();

private:
	Sprite* mSprite;
}; 
