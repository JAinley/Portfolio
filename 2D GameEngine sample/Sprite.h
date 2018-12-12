#include <HAPI_lib.h>
#include <HAPI_InputCodes.h>
#include "Rectangle.h"

class cRectangle;

using namespace HAPISPACE;


#pragma once
class Sprite
{
public:
	Sprite();
	virtual ~Sprite();

	//bool LoadTexture(const std::string &filename, BYTE** Data, unsigned int &width, unsigned int &height);
	void SpriteStart(std::string directory);
	void BlitSpr(BYTE *destination, unsigned int destWdth, unsigned int PosX, unsigned int PosY);

	//clips the image to only parts of ull image can be rendered
	void ClipBlit(BYTE *destination, unsigned int destWdth,  int PosX,  int PosY, unsigned int destHeight, int framewidth, int frameheight, int framenumber);

	//returns height and width of clipped rectangle
	unsigned int Width() const { return ClippedRect.GetWidth(); }
	unsigned int Height() const { return ClippedRect.GetHeight(); }

	const cRectangle& GetFrameRect() const { return ClippedRect; }
	
	cRectangle spriteRect;

private:
	unsigned int PosX;
	unsigned int PosY;
	BYTE* textureData{nullptr};
	int frameNum{ 0 };
	cRectangle FrameRect;
	// creates the two rectangles to clip
	cRectangle ClippedRect;
	cRectangle destRect;


	unsigned int texWidth;
	unsigned int texHeight;
};

