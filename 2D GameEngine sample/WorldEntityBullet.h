#pragma once
#include "WorldEntity.h"
class WorldEntityBullet :
	public WorldEntity
{
public:
	WorldEntityBullet();
	~WorldEntityBullet();

	

	void Movement();
	virtual void Update()
	{
		sides::neutral;
	};

private:

};

