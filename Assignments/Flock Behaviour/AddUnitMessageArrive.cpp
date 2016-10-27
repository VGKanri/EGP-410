#include "Game.h"

AddUnitMessageArrive::AddUnitMessageArrive(Sprite* sprite)
	:GameMessage(ADD_UNIT_MESSAGE_ARRIVE)
	,mSprite(sprite)
{
}

AddUnitMessageArrive::~AddUnitMessageArrive()
{
}

void AddUnitMessageArrive::process()
{
	Vector2D position = gpGame->getUnitManager()->getUnit(0)->getPosition();
	position.setX(position.getX() + 200);
	gpGame->getUnitManager()->addUnit(position, mSprite);
	gpGame->getUnitManager()->getUnit(gpGame->getUnitManager()->getListLength() - 1)->dynamicArrive(gpGame->getUnitManager()->getUnit(0));
}