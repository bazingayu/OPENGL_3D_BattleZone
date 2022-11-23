#include "AutoWarObject.h"

AutoWarObject::AutoWarObject()
{
	life = false;
}

AutoWarObject::~AutoWarObject()
{
}

void AutoWarObject::setParameters(TVector initAccele)
{
	accele = initAccele;
}

void AutoWarObject::setPosition(float x, float y, float z)
{
	currentPosition(x, y, z);
}

void AutoWarObject::setLifeStatus(bool lifeStatus)
{
	this->life = lifeStatus;
}

void AutoWarObject::startMove(TVector initPosition, TVector initVelocity)
{
	life = true;
	currentPosition = initPosition;
	velocity = initVelocity;
}

void AutoWarObject::updateVelocity(float restTime)
{
	velocity += accele*restTime;
}

void AutoWarObject::updatePosition(float restTime)
{
	oldPosition = currentPosition;
	currentPosition = oldPosition + velocity* restTime;
}
