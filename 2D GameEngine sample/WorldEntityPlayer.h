#pragma once
#include "WorldEntity.h"
class WorldEntityPlayer :
	public WorldEntity
{
public:
	WorldEntityPlayer();
	~WorldEntityPlayer();



	int getPosX() { return PosX; }
	int getPosY() { return PosY; }

	void Movement() override final;
virtual void Update()
	{
	//changes the frame to be displayed
	if (currentFrame < FrameNUmber)
	{
		currentFrame++;
		if (currentFrame == FrameNUmber)
		{
			currentFrame = 0;
		}
	}
	sides::Friendly;


	};

private:
	int PosX = 100;
	int PosY = 250;
	int PlayerSpeed = 20;

};

