#pragma once
#include "WorldEntity.h"
class WorldEntityEnemy :
	public WorldEntity
{
public:
	WorldEntityEnemy();
	~WorldEntityEnemy();

	void Movement();
	virtual void Update()
	{
		if (currentFrame < FrameNUmber)
		{
			currentFrame++;
			if (currentFrame == FrameNUmber)
			{
				currentFrame = 0;
			}
		}
		sides::Enemy;
	};
private:
	
};

