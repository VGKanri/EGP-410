#ifndef ADD_UNIT_MESSAGE_WANDER_AND_FLEE_H
#define ADD_UNIT_MESSAGE_WANDER_AND_FLEE_H

#include "GameMessage.h"
#include "Vector2D.h"
#include "Sprite.h"

class Vector2D;

class AddUnitMessageWanderAndFlee :public GameMessage
{
public:
	AddUnitMessageWanderAndFlee(Sprite* sprite);
	~AddUnitMessageWanderAndFlee();

	void process();

private:
	Sprite* mSprite;
};

#endif
