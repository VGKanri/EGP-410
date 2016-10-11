#include "Game.h"
#include "KinematicUnit.h"
#include "GameMessageManager.h"
#include "AddUnitMessageWanderAndSeek.h"

AddUnitMessageWanderAndSeek::AddUnitMessageWanderAndSeek(Sprite* sprite)
	:GameMessage(ADD_UNIT_MESSAGE_SEEK)
	, mSprite(sprite)
{
}

AddUnitMessageWanderAndSeek::~AddUnitMessageWanderAndSeek()
{
}

void AddUnitMessageWanderAndSeek::process()
{
	Vector2D position = gpGame->getUnitManager()->getUnit(0)->getPosition();
	position.setX(position.getX() + 200);
	gpGame->getUnitManager()->addUnit(position, mSprite, false);
	gpGame->getUnitManager()->getUnit(gpGame->getUnitManager()->getListLength() - 1)->wanderAndSeek(gpGame->getUnitManager()->getUnit(0));
	gpGame->getUnitManager()->getUnit(gpGame->getUnitManager()->getListLength() - 1)->getSteering()->setIsWander(true);
	gpGame->getUnitManager()->getUnit(gpGame->getUnitManager()->getListLength() - 1)->setFlee(false);
}