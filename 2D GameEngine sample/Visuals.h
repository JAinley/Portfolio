#include <HAPI_lib.h>
#include <HAPI_InputCodes.h>
#include "Sprite.h"
#include <unordered_map>

using namespace HAPISPACE;

#pragma once

class Sprite;

class Visuals
{
public:
	//creates an unorded map f sprites to store thm in one container
	std::unordered_map<std::string, class Sprite*> sprites;

	Visuals();
	~Visuals();
	void SetPixel(BYTE *screen, unsigned int x, unsigned int y, HAPI_TColour Star1);
	void StartScreenUp();
	void ClearToColour();
	void StarField();

	void LoadSprite(std::string id, std::string directory);
	void Blit(std::string id, unsigned int PosX, unsigned int PosY);
	void Render(std::string id, unsigned int PosX, unsigned int PosY, int Framenumber, int framewidth, int frameheight);

	const cRectangle& GetFrameRect(const std::string &spritename) const;

	Sprite* getSprite(std::string id) { return sprites[id]; }
	//cRectangle& getSpriteRect(std::string id) { return sprites[id]->spriteRect; }

private:
	struct Star { float StarX, StarY, StarZ; };
	// this is the code for setting the star colour and the clear colour
	//screen clear colour
	HAPI_TColour Screencolour = HAPI_TColour(0, 0, 0);
	//set the star colour
	HAPI_TColour Star1 = HAPI_TColour(255, 255, 255);
	//size of the screen
	HAPI_TColour Pixel = HAPI_TColour(0, 0, 255);

	// array of stars
	const unsigned int KnumStars{ 1000 };
	// the centre of the screen
	const int Cx{ 400 };
	const int Cy{ 300 };

	unsigned int eyeDistance{ 50 };

	//screen height and width are set here and a null screen pointer to point to the first pixel on the screen
	unsigned int Height { 450 };
	unsigned int Width{ 1030 };
	BYTE *screen{ nullptr };


	Star stars[1000];
};

