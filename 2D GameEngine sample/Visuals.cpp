#include "Visuals.h"
#include "Sprite.h"

Visuals::Visuals()
{

}


Visuals::~Visuals()
{
	for (auto p : sprites)
		delete p.second;
}

void Visuals::StartScreenUp()
{
	//initialises HAPI core
	if (!HAPI.Initialise(Width, Height))
		return;

	screen = HAPI.GetScreenPointer();

	//sets values for the starfield effect
	for (unsigned int i = 0; i < KnumStars; i++)
	{
		stars[i].StarX = float( rand() % 800);
		stars[i].StarY = float(rand() % 600);
		stars[i].StarZ = float(rand() % 500);
	}
}

//creates a starfield illusion of the stars coming towards screen
void Visuals::StarField()
{
	for (unsigned int i = 0; i < KnumStars; i++)
	{
		if (stars[i].StarZ > 0)
		{
			stars[i].StarZ -= 0.1f;
		}
		else {
			stars[i].StarX = float(rand() % 800);
			stars[i].StarY = float(rand() % 600);
			stars[i].StarZ = float(500);
		}
		float Sx = ((eyeDistance*(stars[i].StarX - Cx)) / (stars[i].StarZ + eyeDistance)) + Cx;
		float Sy = ((eyeDistance*(stars[i].StarY - Cy)) / (stars[i].StarZ + eyeDistance)) + Cy;
		if (Sx <= float(800) && Sy <= float(600)) {
			// pass in the Sy and Sx with the colour of the star and only do this if the stars are inside the screen
			SetPixel(screen, unsigned int(Sx), unsigned int(Sy), Star1);
		}

	}
}


void Visuals::ClearToColour()
{
	//sets the whole screen to a specific colour
	for (unsigned int i = 0; i < Width*Height; i++)
	{
		memcpy(screen + i * 4, &Screencolour, sizeof(Screencolour));
	}
}

//set one pixel or many on the screen to any colour
void Visuals::SetPixel(BYTE *screen, unsigned int x, unsigned int y, HAPI_TColour Star1)
{
	unsigned int offset = (y*Width + x) * 4;
	memcpy(screen + offset, &Star1, sizeof(Star1));

}

//loads sprite data
void Visuals::LoadSprite(std::string id, std::string directory)
{
	Sprite *CSprite = new Sprite;
	sprites[id] = CSprite;
	sprites[id]->SpriteStart(directory);
}

//passes sprite id into blit function which is just a normal render
void Visuals::Blit(std::string id, unsigned int PosX, unsigned int PosY)
{
	sprites[id]->BlitSpr(screen, Width, PosX, PosY);
}

//passes the sprite id in the more complex clippped blitting image function
void Visuals::Render(std::string id, unsigned int PosX, unsigned int PosY, int Framenumber, int framewidth, int frameheight)
{
	sprites[id]->ClipBlit(screen, Width, PosX, PosY, Height, framewidth, frameheight, Framenumber);
}

//gets frame rectangle
const cRectangle & Visuals::GetFrameRect(const std::string &spritename) const
{
	return sprites.at(spritename)->GetFrameRect();
}
