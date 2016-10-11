#include "WanderAndSeek.h"
#include "KinematicUnit.h"
#include "Game.h"

WanderAndSeek::WanderAndSeek(KinematicUnit *pMover, KinematicUnit* pTarget, bool isWander)
	:mpMover(pMover),
	mpTarget(pTarget),
	mIsWander(isWander)
{
	mApplyDirectly = true;
}

Steering* WanderAndSeek::getSteering()
{
	if (mIsWander)
	{
		mLinear = mpMover->getOrientationAsVector() * mpMover->getMaxVelocity();
		mAngular = mpMover->getOrientation() * (genRandomBinomial() * MAX_WANDER_ROTATION);
		std::cout << mIsWander;
		return this;
	}
	else
	{

		mLinear = mpTarget->getPosition() - mpMover->getPosition();
		mLinear.normalize();
		mLinear *= mpMover->getMaxVelocity();
		mAngular = 0;
		std::cout << mIsWander;
		return this;
	}
}

Steering* WanderAndSeek::setIsWander(bool isWander)
{

}