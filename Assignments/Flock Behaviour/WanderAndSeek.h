#ifndef WANDER_SEEK_H
#define WANDER_SEEK_H

#include "Steering.h"

class KinematicUnit;

class WanderAndSeek :public Steering
{
public:
	WanderAndSeek(KinematicUnit* pMover, KinematicUnit* pTarget, bool isWander);
	~WanderAndSeek() {};

	virtual Steering* getSteering();
	void setIsWander(bool wander);

private:
	KinematicUnit* mpMover;
	KinematicUnit* mpTarget;
	bool mIsWander;
}; 

#endif