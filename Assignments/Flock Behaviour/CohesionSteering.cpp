#include "CohesionSteering.h"
#include "Game.h"

CohesionSteering::CohesionSteering(KinematicUnit* pMover, float radius)
{
	mpMover = pMover;
	mRadius = radius;
}

Steering* CohesionSteering::getSteering()
{
	mLinear = Vector2D(0, 0);
	int mNumNearby = 0; //Number of nearby boids

	//For the size of the unit list, other than the player and walls
	for (int i = 5; i < gpGame->getUnitManager()->getListLength(); ++i)
	{
		//If the mover's position minus the other units position is within the separation radius, and is not the same unit
		if  (((mpMover->getPosition() - gpGame->getUnitManager()->getUnit(i)->getPosition()).getLength() < mRadius)
			&& (mpMover->getPosition() - gpGame->getUnitManager()->getUnit(i)->getPosition()).getLength() > -mRadius
			&& mpMover != gpGame->getUnitManager()->getUnit(i))
		{
			++mNumNearby;	//Increase the number of nearby boids
			mLinear += gpGame->getUnitManager()->getUnit(i)->getPosition();	//At that position to the mLinear
		}
	}

	if (mNumNearby == 0)
		return this;

	mLinear /= mNumNearby;
	mLinear = mLinear - mpMover->getPosition();
	mLinear.normalize();

	return this;
}

