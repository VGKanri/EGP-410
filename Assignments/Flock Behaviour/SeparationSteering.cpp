#include "SeparationSteering.h"
#include "Game.h"

SeparationSteering::SeparationSteering(KinematicUnit* pMover, float radius)
{
	mpMover = pMover;
	mRadius = radius;
}

SeparationSteering::~SeparationSteering()
{
}

Steering* SeparationSteering::getSteering()
{
	mLinear = Vector2D(0, 0);
	int mNumNearby = 0;

	//For the number of units in the list sans the walls and player
	for (int i = 5; i < gpGame->getUnitManager()->getListLength(); ++i)
	{
		if (((mpMover->getPosition() - gpGame->getUnitManager()->getUnit(i)->getPosition()).getLength() < mRadius)
			&& (mpMover->getPosition() - gpGame->getUnitManager()->getUnit(i)->getPosition()).getLength() > -mRadius
			&& mpMover != gpGame->getUnitManager()->getUnit(i))
		{
			++mNumNearby;	//Increase the number of nearby boids
			mLinear += mpMover->getPosition() - gpGame->getUnitManager()->getUnit(i)->getPosition();	//At that position to the mLinear
		}
	}
	if (mNumNearby == 0)
		return this;

	mLinear /= mNumNearby;
	mLinear.normalize();

	return this;
}