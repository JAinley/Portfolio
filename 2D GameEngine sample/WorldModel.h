#include <HAPI_lib.h>
#include <HAPI_InputCodes.h>
#include "WorldEntity.h"
#include "Visuals.h"
#include "Sprite.h"

#pragma once
class WorldModel
{
public:

	WorldModel();
	~WorldModel();
	//creates the vector of entities in the world
	std::vector<WorldEntity*> worldEntities;
	void SpawnEnemy();

	void Shoot();

	Visuals CScreen;

	bool LoadWorld();

	void Run();
private:
	HAPI_TColour colour{ 255, 255, 255 };
	const int deadzone = 5000;
	DWORD LastTimeUpdate = 0;
	DWORD LastTimeUpdateShoot = 0;
};

