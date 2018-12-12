#include "WorldEntity.h"
#include <HAPI_lib.h>
#include <HAPI_InputCodes.h>
#include "Visuals.h"
#include "Sprite.h"
#include <string>

WorldEntity::WorldEntity()
{
}


WorldEntity::~WorldEntity()
{

}

void WorldEntity::Collision(WorldEntity* otherEntity)
{
	hasCollided = false;

	cRectangle a = EntityRect;
	cRectangle b = otherEntity->EntityRect;

	//moves the rectangle to the current position of the objects being checked
	a.Translate(WorldPosX, WorldPosY);
	b.Translate(otherEntity->WorldPosX, otherEntity->WorldPosY);

	//checks the rectangles colliding
	if (a.intersect(b) || b.intersect(a) || (!a.Contains(b)) || (!b.Contains(a)))
	{
		hasCollided = true;
	}

	//if collision is true score goes up and the other object is killed off
	if (hasCollided == true)
	{
		hasCollided = true;
		setHealth(1);
		otherEntity->IsAlive = false;
		setScore(1);
		//checks to see if collsion has occured and outputs the check

		if (hasCollided == true)
		{
			HAPI.DebugText("collided");
		}
		else
		{
			HAPI.DebugText("not collided");
		}
		return;
	}


}

void WorldEntity::Render(Visuals &CScreen)
{
	if (IsAlive) {
		//checks which state the entity animation is in and then renders that specific sprite
		if (running == anim::one)
		{
			CScreen.Render(MSpriteRight, WorldPosX, WorldPosY, currentFrame, FrameWidth, FrameHeight);
		}

		if (running == anim::two)
		{
			CScreen.Render(MSpriteLeft, WorldPosX, WorldPosY, currentFrame, FrameWidth, FrameHeight);
		}
		if (running == anim::three)
		{
			CScreen.Render(MSpriteMiddle, WorldPosX, WorldPosY, currentFrame, FrameWidth, FrameHeight);
		}
	}


}

void WorldEntity::Start(std::string spritenameright, std::string spritenamemiddle, std::string spritenameleft, int x, int y, cRectangle &SpriteRect, int Framenumber, int frameheight, int framewidth, std::string tag)
{
	//this gives values to all the member varibles 
	WorldPosX = x;
	WorldPosY = y;
	MSpriteLeft = spritenameleft;
	MSpriteRight = spritenameright;
	MSpriteMiddle = spritenamemiddle;
	FrameNUmber = Framenumber;
	FrameHeight = frameheight;
	FrameWidth = framewidth;
	Tag = tag;

	//sets the frame rectangle size
	EntityRect.left = 0;
	EntityRect.top = 0;
	EntityRect.right = FrameWidth - (FrameWidth/2);
	EntityRect.bottom = FrameHeight ;


}



void WorldEntity::ifDead(WorldEntity &otherEntity)
{
	//if the entity is dead it moves it posiotn to 0,0
	if (IsAlive == false)
	{
		//moves the position back to 0,0
		otherEntity.WorldPosX = 0;
		otherEntity.WorldPosY = 0;
	}
}