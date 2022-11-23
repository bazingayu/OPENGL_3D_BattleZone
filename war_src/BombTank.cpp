#include "BombTank.h"

BombTank::BombTank()
{
	bombType = tankBomb_Type;	//bomb of myTank
	minusLifeDelta = 2;
}

void BombTank::draw()
{
	if(getLifeStatus())
	{
		//printf("current position of bomb tank  %2f		%2f		%2f\n", currentPosition.X(), currentPosition.Y(), currentPosition.Z());
		glPushMatrix();
		glTranslated(currentPosition.X(), currentPosition.Y(), currentPosition.Z());
		glutSolidSphere(1.0, 10, 10);
		glPopMatrix();
	}
	explosion.draw();
}

