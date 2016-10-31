#ifndef STATEMANAGER_H
#define STATEMANAGER_H

#include "Trackable.h"

enum SelectedProperty
{
	ALIGNMENT_WEIGHT,
	COHESION_WEIGHT,
	SEPARATION_WEIGHT,
	MAX_VELOCITY,
	ROT_VELOCITY,
	REACTION_RADIUS
};

static const std::string AL_WEIGHT = "[A] Alignment Weight: ";
static const std::string COH_WEIGHT = "[C] Cohesion Weight: ";
static const std::string SEP_WEIGHT = "[S] Separation Weight: ";
static const std::string M_VELOCITY = "[V] Max Velocity: ";
static const std::string ROT_VEL = "[E] Rotational Velocity: ";
static const std::string REACTION_RAD = "[R] Reaction Radius: ";

enum DebugState
{
	ON,
	OFF
};

class StateManager : public Trackable
{
public:
	StateManager();
	~StateManager();

	void update();

	void setDebugState(DebugState state) { mDebugState = state; }
	void setSelectedProperty(SelectedProperty prop) { mSelectedProperty = prop; }

	DebugState getDebugState() const { return mDebugState; }
	SelectedProperty getSelectedProperty() const { return mSelectedProperty; }

	void saveData() const;
	void loadData();

	//Getters and setters for the weights
	float getAlignWeight() const { return mAlignWeight; }
	float getCohWeight() const { return mCohWeight; }
	float getSepWeight() const { return mSepWeight; }

	void setAlignWeight(float weight) { mAlignWeight = weight; }
	void setCohWeight(float weight) { mCohWeight = weight; }
	void setSepWeight(float weight) { mSepWeight = weight; }

	void addStat();
	void subStat();

private:
	DebugState mDebugState;
	SelectedProperty mSelectedProperty;
	
	float mAlignWeight;
	float mCohWeight;
	float mSepWeight;

	float mMaxVelocity;
	float mRotVelocity;
	float mReactRadius;
};

#endif