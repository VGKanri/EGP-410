#include "Game.h"

AddUnitMessageSeek::AddUnitMessageSeek(Sprite* sprite)
	:GameMessage(ADD_UNIT_MESSAGE_SEEK)
	,mSprite(sprite)
{
}

AddUnitMessageSeek::~AddUnitMessageSeek()
{
}

void AddUnitMessageSeek::process()
{
	Vector2D position = gpGame->getUnitManager()->getUnit(0)->getPosition();
	position.setX(position.getX() + 100);
	gpGame->getUnitManager()->addUnit(position, mSprite);
	gpGame->getUnitManager()->getUnit(gpGame->getUnitManager()->getListLength() - 1)->dynamicSeek(gpGame->getUnitManager()->getUnit(0));
}