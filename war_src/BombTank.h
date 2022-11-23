#ifndef _BOMBTANK_H_
#define _BOMBTANK_H_

#include "IncludeS.h"
#include "Bomb.h"

class BombTank : public Bomb
{
public:
	BombTank();
	
	void draw();
};

#endif