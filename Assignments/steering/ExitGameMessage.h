#pragma once

#include "GameMessage.h"
#include "Vector2D.h"

class Vector2D;

class ExitGameMessage :public GameMessage
{
public:
	ExitGameMessage();
	~ExitGameMessage();

	void process();

private:
}; 
