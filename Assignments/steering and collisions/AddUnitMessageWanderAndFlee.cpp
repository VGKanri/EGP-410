#include "Game.h"
#include "KinematicUnit.h"
#include "GameMessageManager.h"
#include "AddUnitMessageWanderAndFlee.h"

AddUnitMessageWanderAndFlee::AddUnitMessageWanderAndFlee(Sprite* sprite)
	:GameMessage(ADD_UNIT_MESSAGE_SEEK)
	, mSprite(sprite)
{
}

AddUnitMessageWanderAndFlee::~AddUnitMessageWanderAndFlee()
{
}

void AddUnitMessageWanderAndFlee::process()
{
	Vector2D position = gpGame->getUnitManager()->getUnit(0)->getPosition();
	position.setX(position.getX() + 100);
	gpGame->getUnitManager()->addUnit(position, mSprite, true);
	gpGame->getUnitManager()->getUnit(gpGame->getUnitManager()->getListLength() - 1)->wander();
	gpGame->getUnitManager()->getUnit(gpGame->getUnitManager()->getListLength() - 1)->getSteering()->setIsWander(true);
	gpGame->getUnitManager()->getUnit(gpGame->getUnitManager()->getListLength() - 1)->setFlee(true);
}
