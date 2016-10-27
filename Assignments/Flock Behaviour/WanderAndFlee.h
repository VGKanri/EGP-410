#ifndef WANDER_FLEE_H
#define WANDER_FLEE_H

#include "Steering.h"

class KinematicUnit;

class WanderAndFlee :public Steering
{
public:
	WanderAndFlee(KinematicUnit* pMover, KinematicUnit* pTarget, bool isWander);
	~WanderAndFlee() {};

	virtual Steering* getSteering();

private:
	KinematicUnit* mpMover;
	KinematicUnit* mpTarget;
	bool mIsWander;
};

#endif