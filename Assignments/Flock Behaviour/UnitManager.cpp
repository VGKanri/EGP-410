//Unit manager source file made referencing final project of EGP - 310
//Made in Conjunction with Matthew Makuch and used with permission

#include "UnitManager.h"

UnitManager* UnitManager::mpsInstance = NULL;

UnitManager::UnitManager()
{
	mIsAnimPlaying = true;

	mvpUnitList.resize(0);

}

UnitManager::~UnitManager()
{
	clearUnits();
	delete mpsInstance;
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

void UnitManager::addUnit(Vector2D loc, Sprite* sprite, bool flee)
{
	KinematicUnit* tmpUnit = new KinematicUnit(sprite, loc, 0.0f, 0.0f, 0.0f, 180.0F, 100.0F);

	mvpUnitList.push_back(tmpUnit);
}

void UnitManager::addUnit(Vector2D loc)
{
	KinematicUnit* tmpUnit = new KinematicUnit(loc, 0.0f, 0.0f, 0.0f, 0.0F, 0.0F);

	mvpUnitList.push_back(tmpUnit);
}

void UnitManager::removeUnit(int id)
{
	KinematicUnit* tmpUnit;
	//int skipIndex = -1;

	tmpUnit = mvpUnitList.at(id);

	std::vector<KinematicUnit*> tmpVector;

	for (int j = 0; j < mvpUnitList.size(); j++)
	{
		if (j != id)
		{
			tmpUnit = mvpUnitList.at(j);

			tmpVector.push_back(tmpUnit);
		}
	}

	delete mvpUnitList.at(id);


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
	
	for (int i = 0; i < vectorSize; i++)
	{
		if (checkWallCollisions(mvpUnitList.at(i)) == 1)
		{
			mvpUnitList.at(i)->setPosition(Vector2D(mvpUnitList.at(i)->getPosition().getX() + 26, mvpUnitList.at(i)->getPosition().getY()));
			if (mvpUnitList.at(i) != 0)
			{
				mvpUnitList.at(i)->setVelocity(Vector2D(10.0f, 0.0f));
			}
		}
		else if (checkWallCollisions(mvpUnitList.at(i)) == 2)
		{
			mvpUnitList.at(i)->setPosition(Vector2D(mvpUnitList.at(i)->getPosition().getX() - 26, mvpUnitList.at(i)->getPosition().getY()));
			if (mvpUnitList.at(i) != 0)
			{
				mvpUnitList.at(i)->setOrientation(1.0f);
				mvpUnitList.at(i)->setVelocity(Vector2D(-10.0f, 0.0f));
			}
		}
		else if (checkWallCollisions(mvpUnitList.at(i)) == 3)
		{
			mvpUnitList.at(i)->setPosition(Vector2D(mvpUnitList.at(i)->getPosition().getX(), mvpUnitList.at(i)->getPosition().getY() + 26));
			if (mvpUnitList.at(i) != 0)
			{
				mvpUnitList.at(i)->setOrientation(1.0f);
				mvpUnitList.at(i)->setVelocity(Vector2D(0.0f, 10.0f));
			}
		}
		else if (checkWallCollisions(mvpUnitList.at(i)) == 4)
		{
			mvpUnitList.at(i)->setPosition(Vector2D(mvpUnitList.at(i)->getPosition().getX() + 26, mvpUnitList.at(i)->getPosition().getY() - 26));
			if (mvpUnitList.at(i) != 0)
			{
				mvpUnitList.at(i)->setOrientation(1.0f);
				mvpUnitList.at(i)->setVelocity(Vector2D(0.0f, -10.0f));
			}
		}
	}
	

	targetAvoidance();
	
}

void UnitManager::drawUnits(GraphicsSystem* system, GraphicsBuffer* buffer)
{
	int vectorSize = mvpUnitList.size();

	for (int i = 0; i < vectorSize; i++)
	{
		if (mvpUnitList.at(i) != NULL && !mvpUnitList.at(i)->getIsWall())
		{
			mvpUnitList.at(i)->draw(buffer);
		}
	}
}

void UnitManager::targetAvoidance()
{
	int vectorSize = mvpUnitList.size();
	for (int i = 0; i < vectorSize; i++)
	{
		if (mvpUnitList.at(i) != NULL)
		{
			for (int j = 0; j < vectorSize; j++)
			{
				if (j != i && checkLocations(mvpUnitList.at(i)->getPosition(), mvpUnitList.at(j)->getPosition(), true) 
					&& mvpUnitList.at(i) != 0 && j == 0 && j != 1 && j !=2 && j != 3 && j != 4
					&& i != 1 && i != 2 && i != 3 && i != 4)
				{
					
					if (mvpUnitList.at(i)->getFlee() == true)
					{
						Steering* nSteering = new WanderAndFlee(mvpUnitList.at(i), mvpUnitList.at(0), false);
						mvpUnitList.at(i)->setSteering(nSteering);

					}

					else if (mvpUnitList.at(i)->getFlee() == false)
					{
						Steering* nSteering = new WanderAndSeek(mvpUnitList.at(i), mvpUnitList.at(0), false);
						mvpUnitList.at(i)->setSteering(nSteering);
					}
					

				}
				else if (j != i && checkLocations(mvpUnitList.at(i)->getPosition(), mvpUnitList.at(j)->getPosition(), false) 
					&& mvpUnitList.at(i) != 0 && mvpUnitList.at(j) != 0 && j != 1 && j != 2 && j != 3 && j != 4
					&& i != 1 && i != 2 && i != 3 && i != 4)
				{
					mvpUnitList.at(i)->dynamicFlee(mvpUnitList.at(j));
				}
				else if (j != i && !checkLocations(mvpUnitList.at(i)->getPosition(), mvpUnitList.at(j)->getPosition(), true) 
					&& mvpUnitList.at(i) != 0 && j != 1 && j != 2 && j != 3 && j != 4
					&& i != 1 && i != 2 && i != 3 && i != 4)
				{
					if (mvpUnitList.at(i)->getFlee() == true)
					{
						Steering* nSteering = new WanderAndFlee(mvpUnitList.at(i), mvpUnitList.at(0), true);
						mvpUnitList.at(i)->setSteering(nSteering);
					}
					
					else if (mvpUnitList.at(i)->getFlee() == false)
					{
						Steering* nSteering = new WanderAndSeek(mvpUnitList.at(i), mvpUnitList.at(0), true);
						mvpUnitList.at(i)->setSteering(nSteering);
					}
				}
			}
		}
	}
}

bool UnitManager::checkLocations(Vector2D lhs, Vector2D rhs, bool isPlayer)
{
	if (((lhs.getX() > rhs.getX() - AVOIDANCE_RADIUS) && (lhs.getX() < rhs.getX()
		+ AVOIDANCE_RADIUS)) && ((lhs.getY() > rhs.getY() - AVOIDANCE_RADIUS) && (lhs.getY() < (rhs.getY() + AVOIDANCE_RADIUS))) && isPlayer)
		return true;
	else if (((lhs.getX() > rhs.getX() - FLEE_RADIUS) && (lhs.getX() < rhs.getX() + FLEE_RADIUS))
		&& ((lhs.getY() > rhs.getY() - FLEE_RADIUS) && (lhs.getY() < (rhs.getY() + FLEE_RADIUS))) && !isPlayer)
		return true;
	else
		return false;
}

int UnitManager::checkWallCollisions(KinematicUnit* unit)
{
	if (unit->getPosition().getX() < mvpUnitList.at(1)->getPosition().getX() + 20 
		&& ((unit->getPosition().getX() != mvpUnitList.at(1)->getPosition().getX()) 
		&& unit->getPosition().getY() != mvpUnitList.at(1)->getPosition().getY()))
	{
		return 1;
	}

	else if (unit->getPosition().getX() > mvpUnitList.at(2)->getPosition().getX() - 20
		&& ((unit->getPosition().getX() != mvpUnitList.at(2)->getPosition().getX())
		&& unit->getPosition().getY() != mvpUnitList.at(2)->getPosition().getY()))
	{
		return 2;
	}

	else if (unit->getPosition().getY() < mvpUnitList.at(3)->getPosition().getY() + 20
		&& ((unit->getPosition().getX() != mvpUnitList.at(3)->getPosition().getX())
		&& unit->getPosition().getY() != mvpUnitList.at(3)->getPosition().getY()))
	{
		return 3;
	}
	else if (unit->getPosition().getY() > mvpUnitList.at(4)->getPosition().getY() - 20
		&& ((unit->getPosition().getX() != mvpUnitList.at(4)->getPosition().getX())
		&& unit->getPosition().getY() != mvpUnitList.at(4)->getPosition().getY()))
	{
		return 4;
	}

	return 5;
}