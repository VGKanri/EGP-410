#include "Game.h"
#include "KinematicUnit.h"
#include "GameMessageManager.h"
#include "ExitGameMessage.h"

ExitGameMessage::ExitGameMessage()
	:GameMessage(EXIT_GAME_MESSAGE)
{
}

ExitGameMessage::~ExitGameMessage()
{
}

void ExitGameMessage::process()
{
	gpGame->setShouldEnd(true);
}