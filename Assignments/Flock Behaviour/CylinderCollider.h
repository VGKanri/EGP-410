#ifndef CYLINDERCOLLIDER_H
#define CYLINDERCOLLIDER_H

#include "Trackable.h"
#include "Vector2D.h"

class CylinderCollider : public Trackable
{
public:
	//Constructors and destructors
	CylinderCollider();
	~CylinderCollider();

	void update(Vector2D positionChange);
	bool checkCollision(CylinderCollider& cylinder);

private:
	Vector2D mPosition;
	float mRadius;
};

#endif
