#include "GroupAlignmentSteering.h"
#include "AlignmentSteering.h"
#include "CohesionSteering.h"
#include "SeparationSteering.h"
#include "KinematicUnit.h"

#include "KinematicWanderSteering.h"
#include "Game.h"

GroupAlignmentSteering::GroupAlignmentSteering(KinematicUnit* pMover, float alignWeight, float sepWeight, float cohWeight)
{
	mpMover = pMover;
	mApplyDirectly = false;

	mpAlignmentSteering = new AlignmentSteering(mpMover, 160.0f);
	mpCohesionSteering = new CohesionSteering(mpMover, 160.0f);
	mpSeparationSteering = new SeparationSteering(mpMover, 80.0f);

	mAlignWeight = alignWeight;
	mSepWeight = sepWeight;
	mCohWeight = cohWeight;
}

GroupAlignmentSteering::~GroupAlignmentSteering()
{
	delete mpAlignmentSteering;
	delete mpCohesionSteering;
	delete mpSeparationSteering;
}

Steering* GroupAlignmentSteering::getSteering()
{
	mpAlignmentSteering->getSteering();
	mpSeparationSteering->getSteering();
	mpCohesionSteering->getSteering();

	mCohWeight = gpGame->getStateManager()->getCohWeight();
	mSepWeight = gpGame->getStateManager()->getSepWeight();
	mAlignWeight = gpGame->getStateManager()->getAlignWeight();

	mLinear = (mpCohesionSteering->getLinear() * mCohWeight)
		+ (mpSeparationSteering->getLinear() * mSepWeight)
		+ (mpAlignmentSteering->getLinear() * mAlignWeight);

	mLinear.normalize();

	mLinear *= mpMover->getMaxVelocity();

	mAngular = 0;

	return this;
}