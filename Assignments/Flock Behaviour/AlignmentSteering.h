#ifndef ALIGNMENTSTEERING_H
#define ALIGNMENTSTEERING_H

#include "Steering.h"
#include <vector>

class KinematicUnit;

class AlignmentSteering : public Steering
{
public:
	AlignmentSteering(KinematicUnit* pMover, float radius);
	~AlignmentSteering();

	virtual Steering* getSteering();
private:
	KinematicUnit* mpMover;
	float mRadius;
};

#endif
