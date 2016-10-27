#ifndef EXIT_GAME_MESSAGE_H
#define EXIT_GAME_MESSAGE_H

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

#endif