#ifndef ADD_UNIT_MESSAGE_ARRIVE_H
#define ADD_UNIT_MESSAGE_ARRIVE_H

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
#endif