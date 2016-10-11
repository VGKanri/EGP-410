#include "WanderAndFlee.h"
#include "KinematicUnit.h"
#include "Game.h"

WanderAndFlee::WanderAndFlee(KinematicUnit *pMover, KinematicUnit* pTarget, bool isWander)
	:mpMover(pMover),
	mpTarget(pTarget),
	mIsWander(isWander)
{
	mApplyDirectly = true;
}

Steering* WanderAndFlee::getSteering()
{
	if (mIsWander)
	{
		mLinear = mpMover->getOrientationAsVector() * mpMover->getMaxVelocity();
		mAngular = mpMover->getOrientation() * (genRandomBinomial() * MAX_WANDER_ROTATION);
		return this;
	}
	else
	{
		mLinear = mpMover->getPosition() - mpTarget->getPosition();

		mLinear.normalize();
		mLinear *= mpMover->getMaxVelocity();
		mAngular = 0;
		return this;
	}
}