#pragma once

#include "Steering.h"

class KinematicUnit;

class KinematicWanderSteering:public Steering
{
public:
	KinematicWanderSteering( KinematicUnit* pMover );
	~KinematicWanderSteering(){};

	virtual Steering* getSteering();

private:
	KinematicUnit* mpMover;
};