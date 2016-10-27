#ifndef REMOVE_UNIT_MESSAGE_H
#define REMOVE_UNIT_MESSAGE_H

#include "GameMessage.h"
#include "Vector2D.h"

class Vector2D;

class RemoveUnitMessage :public GameMessage
{
public:
	RemoveUnitMessage(int id);
	~RemoveUnitMessage();

	void process();

private:
	int mID;
};

#endif