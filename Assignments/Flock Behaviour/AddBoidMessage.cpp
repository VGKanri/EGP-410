#include "AddBoidMessage.h"

#include "Game.h"

AddBoidMessage::AddBoidMessage()
	:GameMessage(ADD_BOID_MESSAGE)
{
}

AddBoidMessage::~AddBoidMessage()
{
}

void AddBoidMessage::process()
{
	Vector2D position, velocity;

	//Adds five boids near each other at the center of the screen
	for (int i = 0; i < 5; ++i)
	{
		position = Vector2D((gpGame->getGraphicsSystem()->getWidth() / 2) + (i * 40),
			(gpGame->getGraphicsSystem()->getHeight() / 2) + (i * 40));

		velocity = Vector2D(50.0f, 50.0f);

		gpGame->getUnitManager()->addUnit(position, gpGame->getSpriteManager()->getSprite(AI_ICON_SPRITE_ID), false);
		gpGame->getUnitManager()->getUnit(gpGame->getUnitManager()->getListLength() - 1)->setVelocity(velocity);
		gpGame->getUnitManager()->getUnit(gpGame->getUnitManager()->getListLength() - 1)->boidBehaviour();
	}
}