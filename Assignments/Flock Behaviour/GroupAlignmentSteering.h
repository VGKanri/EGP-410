#ifndef GROUPALIGNMENTSTEERING_H
#define GROUPALIGNMENTSTEERING_H

#include "Steering.h"

class KinematicUnit;

class GroupAlignmentSteering : public Steering
{
public:
	GroupAlignmentSteering(KinematicUnit* pMover, float alignWeight, float sepWeight, float cohWeight);
	~GroupAlignmentSteering();

	virtual Steering* getSteering();

	//Setters for the steering weights
	void setAlignWeight(float weight) { mAlignWeight = weight; }
	void setSepWeight(float weight) { mSepWeight = weight; }
	void setCohWeight(float weight) { mSepWeight = weight; }

private:
	KinematicUnit* mpMover;

	//Steering containers for each of the different types of steering
	Steering* mpAlignmentSteering;
	Steering* mpSeparationSteering;
	Steering* mpCohesionSteering;

	//Weights for the steering
	float mAlignWeight, mSepWeight, mCohWeight;
};

#endif
