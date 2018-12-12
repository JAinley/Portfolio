#include "WorldEntityBullet.h"



WorldEntityBullet::WorldEntityBullet()
{
}


WorldEntityBullet::~WorldEntityBullet()
{
}

void WorldEntityBullet::Movement()
{
	if (getPositionX() > 2000)
	{
		seDead();
	}
	else
	{
	WorldPosX += 30;
	}	
}
