//Code below is an altered version of code from EGP 310: Final Project
//Created in conjunction with Matthew Makuch (group project) and used with permission

#ifndef UNITMANAGER_H
#define UNITMANAGER_H

using namespace std;

#include "KinematicUnit.h"
#include "GraphicsSystem.h"
#include "GraphicsBufferManager.h"
#include "WanderAndSeek.h"
#include "WanderAndFlee.h"
#include <vector>

class UnitManager : public Trackable
{
private:
	//Private member variables
	std::vector<KinematicUnit*> mvpUnitList; //Container for the kinematic units
	
	GraphicsBuffer* mpSourceBuffer;
	bool mIsAnimPlaying;

	static UnitManager* mpsInstance;

	//KinematicUnit* mpSelectedUnit;

public:
	UnitManager();

	static void init();
	static UnitManager* getInstance() { return mpsInstance; };

	//Public destructor
	~UnitManager();

	//Adding, removing, and getting units from the list
	void addUnit(Vector2D location, Sprite* sprite);
	void addUnit(Vector2D location, Sprite* sprite, bool flee);
	void addUnit(Vector2D location);
	void removeUnit(int id);
	//KinematicUnit* getUnit(Vector2D loc);
	KinematicUnit* getUnit(int id);

	void clearUnits();
	int getListLength() { return mvpUnitList.size(); };

	void updateUnits(float passedTime);
	void drawUnits(GraphicsSystem* drawToSystem, GraphicsBuffer* buffer);

	//std::vector<KinematicUnit*> getUnitList() { return mvpUnitList; };

	//Target avoidance function to keep units away from each other
	void targetAvoidance();
	bool checkLocations(Vector2D lhs, Vector2D rhs, bool isPlayer);	//Checks if the two unit's locations are within a specified distance of each other
	int checkWallCollisions(KinematicUnit* unit);

};

#endif