#include "Game.h"
#include "KinematicUnit.h"
#include "GameMessageManager.h"
#include "RemoveUnitMessage.h"
#include <time.h>

RemoveUnitMessage::RemoveUnitMessage(int id)
	:GameMessage(REMOVE_UNIT_MESSAGE)
	, mID(id)
{
}

RemoveUnitMessage::~RemoveUnitMessage()
{
}

void RemoveUnitMessage::process()
{
	srand(time(NULL));
	mID = rand() % (gpGame->getUnitManager()->getListLength() - 1) + 1;
	gpGame->getUnitManager()->removeUnit(mID);
}