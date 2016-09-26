//Unit manager source file made referencing final project of EGP - 310
//Made in Conjunction with Matthew Makuch and used with permission

#include "UnitManager.h"

UnitManager* UnitManager::mpsInstance = NULL;

UnitManager::UnitManager()
{
	mIsAnimPlaying = true;

	//Maybe where selected unit goes

	mvpUnitList.resize(0);

	//PUT GRAPHICS BUFFER HERE PROBABLY
}

UnitManager::~UnitManager()
{
	clearUnits();
	//Remove listeners if needed
}

void UnitManager::init()
{
	if (mpsInstance == NULL)
	{
		mpsInstance = new UnitManager;
	}
}

//Adding removing and getting unit functions
void UnitManager::addUnit(Vector2D loc, Sprite* sprite)
{
	KinematicUnit* tmpUnit = new KinematicUnit(sprite, loc, 0.0f, 0.0f, 0.0f, 180.0F, 100.0F);

	mvpUnitList.push_back(tmpUnit);
}

void UnitManager::removeUnit(int id)
{
	KinematicUnit* tmpUnit;
	//int skipIndex = -1;

	tmpUnit = mvpUnitList.at(id);

	delete mvpUnitList.at(id);
	
	std::vector<KinematicUnit*> tmpVector;

	for (int j = 0; j < mvpUnitList.size(); j++)
	{
		if (j != id)
		{
			tmpUnit = mvpUnitList.at(j);

			tmpVector.push_back(tmpUnit);
		}
	}

	mvpUnitList = tmpVector;
}

//Gets a unit at the specified ID location
KinematicUnit* UnitManager::getUnit(int id)
{
	return mvpUnitList.at(id);
}

//Fucntion for clearing the units out of the list in case of deletion or a reset
void UnitManager::clearUnits()
{
	int numDeletesNeeded = mvpUnitList.size();

	for (int i = 0; i < numDeletesNeeded; i++)
	{
		delete mvpUnitList.at(i);
	}

	mvpUnitList.resize(0);
}

//Updates all units in the unit manager
void UnitManager::updateUnits(float timePassed)
{
	int vectorSize = mvpUnitList.size();

	for (int i = 0; i < vectorSize; i++)
	{
		mvpUnitList.at(i)->update(timePassed);
	}
}

void UnitManager::drawUnits(GraphicsSystem* system, GraphicsBuffer* buffer)
{
	int vectorSize = mvpUnitList.size();

	for (int i = 0; i < vectorSize; i++)
	{
		if (mvpUnitList.at(i) != NULL)
		{
			mvpUnitList.at(i)->draw(buffer);
		}
	}
}