#ifndef SEPARATIONSTEERING_H
#define SEPARATIONSTEERING_H

#include "Steering.h"
#include <vector>

class KinematicUnit;

class SeparationSteering : public Steering
{
public:
	SeparationSteering(KinematicUnit* pMover, float radius);
	~SeparationSteering();

	virtual Steering* getSteering();
private:
	KinematicUnit* mpMover;
	float mRadius;
};

#endif