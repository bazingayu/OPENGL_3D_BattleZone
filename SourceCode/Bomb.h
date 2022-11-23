#ifndef _BOMB_H_
#define _BOMB_H_

#include "IncludeS.h"
#include "war_src/AutoWarObject.h"
#include "war_src/Explosion.h"

class Bomb : public AutoWarObject
{
protected:
	unsigned int bombType;		//bomb of myTank = 1;
	unsigned int minusLifeDelta;
	Explosion explosion;
public:
	Bomb();
	~Bomb();
	
	void setParameters(TVector accle, char *explosionFile, const char *soundFileName);
	void moveToCollisionPoint(float lamda);
	void startExplosion();
	bool getExplosionLifeStatus();
	unsigned int getMinusLifeDelta(){return minusLifeDelta;}
	unsigned int getBombType(){ return bombType;}
	virtual void setAngleWithX(float angleWithX){}
	virtual void updateBombDirection(){}
	virtual void setTargetObject(AutoWarObject *autoWarObject){}
	virtual void setVelocityMag(float velocityMag){}
};

#endif