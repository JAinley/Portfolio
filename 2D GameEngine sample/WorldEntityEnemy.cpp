#include "WorldEntityEnemy.h"



WorldEntityEnemy::WorldEntityEnemy()
{
}


WorldEntityEnemy::~WorldEntityEnemy()
{
}

void WorldEntityEnemy::Movement()
{
	//enemy player movement goes here
	WorldPosX = WorldPosX - 10;
	running = anim::two;
}