#include "AlignmentSteering.h"
#include "Game.h"

AlignmentSteering::AlignmentSteering(KinematicUnit* pMover, float radius)
{
	mpMover = pMover;
	mRadius = radius;
}

AlignmentSteering::~AlignmentSteering()
{
}

Steering* AlignmentSteering::getSteering()
{
	mLinear = Vector2D(0, 0);
	int mNumNearby = 0;

	for (int i = 0; i < gpGame->getUnitManager()->getListLength(); ++i)
	{
		if (((mpMover->getPosition() - gpGame->getUnitManager()->getUnit(i)->getPosition()).getLength() <= mRadius)
			&& (mpMover->getPosition() - gpGame->getUnitManager()->getUnit(i)->getPosition()).getLength() >= -mRadius
			&& mpMover != gpGame->getUnitManager()->getUnit(i))
		{
			++mNumNearby;	//Increase the number of nearby boids
			mLinear += gpGame->getUnitManager()->getUnit(i)->getVelocity();	//At that unit's velocity to the mLinear
		}
	}

	if (mNumNearby == 0)
		return this;

	mLinear /= mNumNearby;
	mLinear.normalize();

	return this;
}