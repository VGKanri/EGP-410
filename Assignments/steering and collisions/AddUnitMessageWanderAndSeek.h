#pragma once

#include "GameMessage.h"
#include "Vector2D.h"
#include "Sprite.h"

class Vector2D;

class AddUnitMessageWanderAndSeek :public GameMessage
{
public:
	AddUnitMessageWanderAndSeek(Sprite* sprite);
	~AddUnitMessageWanderAndSeek();

	void process();

private:
	Sprite* mSprite;
};
