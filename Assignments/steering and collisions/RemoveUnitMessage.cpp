#include "Game.h"
#include "KinematicUnit.h"
#include "GameMessageManager.h"
#include "RemoveUnitMessage.h"
#include <time.h>


RemoveUnitMessage::RemoveUnitMessage(int id)
	:GameMessage(REMOVE_UNIT_MESSAGE)
	, mID(id)
{
	srand(time(NULL));

}

RemoveUnitMessage::~RemoveUnitMessage()
{
}

void RemoveUnitMessage::process()
{
	do
	{
		mID = rand() % 100;
	} while (mID <= 5 || mID >= gpGame->getUnitManager()->getListLength());
	gpGame->getUnitManager()->removeUnit(mID);
}