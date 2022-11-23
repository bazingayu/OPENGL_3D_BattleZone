#ifndef _COLLISIONSQUARE_H_
#define _COLLISIONSQUARE_H_

#include "IncludeS.h"
#include "Tvector.h"

class CollisionSquare
{
public:
	TVector normal;
	TVector center;
	
public:
	CollisionSquare();
	CollisionSquare(TVector normal, TVector center);
	
	void updateCollisionSquare(TVector normal, TVector center);
	void setParameters(TVector normal, TVector center);
	bool testIntersection(const TVector &position, const TVector &direction, double &lamda);
};

#endif