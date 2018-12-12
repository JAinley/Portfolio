#include "WorldModel.h"
#include "Visuals.h"
#include "WorldEntityPlayer.h"
#include "WorldEntityEnemy.h"
#include "Rectangle.h"
#include "WorldEntityBullet.h"
//#if defined(DEBUG) | defined(_DEBUG)
//#include <crtdbg.h>
//#define new new(_NORMAL_BLOCK,_FILE_, _LINE_)
//#endif



WorldModel::WorldModel()
{

}

WorldModel::~WorldModel()
{
	for (auto p : worldEntities)
		delete p;

}

void WorldModel::Run()
{

	HAPI.SetShowFPS(true);

	DWORD Time = HAPI.GetTime();
	const DWORD Tick{ 60 };
	const DWORD ShootTick{ 5 };
	HAPI.RenderText(200, 5, colour, std::string("Score") + std::string(" ") + std::string(std::to_string(worldEntities[0]->getScore())), 20);
	HAPI.RenderText(300, 5, colour, std::string("Health") + std::string(" ") + std::string(std::to_string(worldEntities[0]->getHealth())), 20);

	if (Time - LastTimeUpdate > Tick)
	{
		const HAPI_TKeyboardData& KeyData = HAPI.GetKeyboardData();
		const HAPI_TControllerData& Controller = HAPI.GetControllerData(0);
		//clear the screen to black
		CScreen.ClearToColour();
		//renders the backgound
		CScreen.Blit("Background", 0, 0);

		//loops through the enitities vector to call the update and other functions
		for (auto p : worldEntities) {

			p->Update();
			p->Movement();

		}
		//updates the  delta time
		LastTimeUpdate = Time;
	}

	{
		const DWORD ShootTick{ 35 };
		if (Time - LastTimeUpdate > ShootTick) {
			//loops through the controllers max and choses the one plugged in
			for (unsigned int i = 0; i < HAPI.GetMaxControllers(); i++) {
				const HAPI_TKeyboardData& KeyData = HAPI.GetKeyboardData();
				const HAPI_TControllerData& Controller = HAPI.GetControllerData(i);
				if (KeyData.scanCode[HK_SPACE] || Controller.digitalButtons[HK_DIGITAL_A])
				{
					//if space is pressed player shoots
					Shoot();

				}
				if (KeyData.scanCode['q'] || Controller.digitalButtons[HK_DIGITAL_B])
				{
					SpawnEnemy();
				}
			}
			LastTimeUpdateShoot = Time;
		}


		//checks collision between bullets and enemies
		for (auto p : worldEntities)
		{
			if (p->getTag() == "Bullet")
			{
				for (auto t : worldEntities)
				{
					if (t->getTag() == "Enemy"  && t->CheckAlive() == true)
					{
						p->Collision(t);
					}
				}
			}
		}

		//checks collision between player and enemies
		for (auto p : worldEntities)
		{
			if (p->getTag() == "Player")
			{
				for (auto t : worldEntities)
				{
					if (t->getTag() == "Enemy" && t->CheckAlive() == true)
					{
						p->Collision(t);
					}
				}
			}
		}
	}

		//loops through the entites and renders them outside of the tick so they are updated a lot quicker
		for (auto p : worldEntities) {

			p->Render(CScreen);
		}
	
}


bool WorldModel::LoadWorld()
{
	//loads everything in the world to be used

	//initialises the screen and HAPI
	CScreen.StartScreenUp();
	CScreen.LoadSprite("CharacterRight", "Data\\RunnningSpriteUse.png");
	CScreen.LoadSprite("CharacterLeft", "Data\\RunningLeft.png");
	CScreen.LoadSprite("CharacterStill", "Data\\characterstill.png");
	CScreen.LoadSprite("Background", "Data\\Background.png");
	CScreen.LoadSprite("Bullet", "Data\\Bullet.png");

	//create the enitites to be put into the vector worldentities and gives the entity a sprite and initial starting positions
	WorldEntityPlayer* PlayerEnities = new WorldEntityPlayer();
	worldEntities.push_back(PlayerEnities);
	PlayerEnities->Start("CharacterRight", "CharacterStill", "CharacterLeft", PlayerEnities->getPosX(), PlayerEnities->getPosY(), CScreen.getSprite("CharacterRight")->spriteRect, 10, 175, 135, "Player");

	WorldEntityEnemy* EnemyEnities = new WorldEntityEnemy();
	worldEntities.push_back(EnemyEnities);
	EnemyEnities->Start("CharacterRight", "CharacterStill", "CharacterLeft", 700, 250, CScreen.getSprite("CharacterRight")->spriteRect, 10, 175, 135, "Enemy");

	//creates multiple enemies ready to be spawned in
	for (unsigned int i = 0; i < 5; i++){
	EnemyEnities = new WorldEntityEnemy();
	worldEntities.push_back(EnemyEnities);
	EnemyEnities->Start("CharacterRight", "CharacterStill", "CharacterLeft", 600, 250, CScreen.getSprite("CharacterRight")->spriteRect, 10, 175, 135, "Enemy");
	EnemyEnities->seDead();
	}

	//creates an array of bullets that are all flagged as dead
	for (int i = 0; i < 50; i++) {
		WorldEntityBullet* Bullet = new WorldEntityBullet();
		worldEntities.push_back(Bullet);
		Bullet->Start("Bullet", "Bullet", "Bullet", 0, 0, CScreen.getSprite("Bullet")->spriteRect, 1, 10, 30, "Bullet");
		Bullet->seDead();
	}
	return true;
}

//here is the shooting code to search through the entities and find the bullets and find which ones are dead
//it then switches one to alive to be fired
void WorldModel::Shoot()
{
	DWORD Time = HAPI.GetTime();
	const DWORD ShootTick{ 40 };
	if (Time - LastTimeUpdate > ShootTick) {
		for (auto p : worldEntities)
		{
			if (p->getTag() == "Player")
			{
				for (auto t : worldEntities)
				{
					if (t->getTag() == "Bullet" && t->CheckAlive() == false)
					{
						if (t->CheckAlive() == true)
						{
							HAPI.RenderText(300, 5, colour, std::string("Reload"), 20);
						}
						else
						{
						t->setAlive();
						t->setPosition(p->getPositionX() + 100, p->getPositionY() + 100);
						HAPI.DebugText("Fire");
						break;
						}
					}
				}
			}
		}
		//updates the  delta time
		LastTimeUpdateShoot = Time;
	}

}

//spawns more enemies
void WorldModel::SpawnEnemy()
{
	DWORD Time = HAPI.GetTime();
	const DWORD ShootTick{ 40 };
	if (Time - LastTimeUpdate > ShootTick) {
				for (auto t : worldEntities)
				{
					if (t->getTag() == "Enemy" && t->CheckAlive() == false)
					{
							t->setAlive();
							t->setPosition(800 , t->getPositionY() );
							HAPI.DebugText("Fire");
							break;
					}
		}
		//updates the  delta time
		LastTimeUpdateShoot = Time;
	}

}









