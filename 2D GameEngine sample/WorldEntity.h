#include <HAPI_lib.h>
#include "Visuals.h"
#include "Rectangle.h"
#include "Sprite.h"

#pragma once

//enum class used for animation states
enum class anim { one, two, three };

//enum class for sides
//----------->work in prgress<-----------!!
enum class sides {Friendly, neutral, Enemy};

class WorldEntity
{
public:
	WorldEntity();
	~WorldEntity();

	//initiales all the values set at the beginning
	void Start(std::string spritenameright, std::string spritenamemiddle, std::string spritenameleft, int x, int y, cRectangle &SpriteRect, int Framenumber, int frameheight, int framewidth, std::string tag);

	//virtual to make all child classes make their own movement function as they will be all different
	virtual void Movement() = 0;

	//checks collisions
	void Collision(WorldEntity* otherEntity);

	//renders the sprites
	void Render(Visuals &CScreen);

	//checks to see if the entity is alive
	bool CheckAlive() { return IsAlive; }
	void seDead() { IsAlive = false; }
	void setAlive() { IsAlive = true; }

	//if the entity is dead this function deals with them
	void ifDead(WorldEntity &otherEntity);

	//gets the entities tag TODO::MAKE IN ENUM CLASS
	std::string getTag() { return Tag; }

	//gets the x and y position
	int getPositionX() { return WorldPosX; }
	int getPositionY() { return WorldPosY; }

	//gets the health and sets health 
	int getHealth() { return Health; }
	void setHealth(int damage) { Health = Health - damage; }

	//gets and sets thr score
	int getScore() { return Score; }
	void setScore(int score) { Score = Score + score; }

	//sets the animation state enum to default
	anim running = anim::three;

	//pure virtual function
	virtual void Update() = 0;

	//sets the positions
	void setPosition(int positionX, int positionY) { WorldPosX = positionX, WorldPosY = positionY; }

protected:
	int WorldPosX;
	int WorldPosY;

	int FrameWidth;
	int FrameHeight;
	int FrameNUmber;
	int currentFrame = 0;

	int direction = 0;
	std::string MSpriteRight;
	std::string MSpriteLeft;
	std::string MSpriteMiddle;

	std::string Tag;

	int MovementSpeed;
	bool IsAlive = true;

	cRectangle EntityRect;

	bool hasCollided = false;

	
	int Health = 100;
	int Damage = 20;

private:
	int Score = 0;

};

