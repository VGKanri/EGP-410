#ifndef COHESIONSTEERING_H
#define COHESIONSTEERING_H

#include "Steering.h"

class KinematicUnit;

class CohesionSteering : public Steering
{
public:
	CohesionSteering(KinematicUnit* pMover, float radius);
	CohesionSteering() {};

	virtual Steering* getSteering();

private:
	KinematicUnit* mpMover;
	float mRadius;
};

#endif
