#pragma once

#include "Steering.h"

class KinematicUnit;

class WanderAndSeek :public Steering
{
public:
	WanderAndSeek(KinematicUnit* pMover, KinematicUnit* pTarget, bool isWander);
	~WanderAndSeek() {};

	virtual Steering* getSteering();

private:
	KinematicUnit* mpMover;
	KinematicUnit* mpTarget;
	bool mIsWander;
}; 
