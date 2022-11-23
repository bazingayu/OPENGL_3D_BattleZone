#ifndef _COLLISIONBOXARRAY_H_
#define _COLLISIONBOXARRAY_H_

#include "IncludeS.h"
#include <vector>
#include "CollisionBox.h"

class CollisionBoxArray
{
private:
	std::vector<CollisionBox *> collisionBoxArray;
public:
	CollisionBoxArray();
	~CollisionBoxArray();
	
	void addCollisionBox(CollisionBox *collisionBox);
	int getCollisionBoxNumber();
	void minusTimeLifeCollBox(unsigned int collBoxNum, int minusTimeDelta);
	CollisionBox *getCollisionBox(int number);
	void draw();
};

#endif