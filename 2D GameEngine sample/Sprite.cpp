#include "Sprite.h"
#include "Rectangle.h"




Sprite::Sprite()
{
}


Sprite::~Sprite()
{
	delete[]textureData;
}

//bool LoadTexture(const std::string &filename, BYTE** Data, unsigned int &width, unsigned int &height);

void Sprite::SpriteStart(std::string directory)
{


	if (!HAPI.LoadTexture(directory, &textureData, texWidth, texHeight)) {
		HAPI.UserMessage("Texture not found", "error");
		return;
	}
	spriteRect.right = texWidth;
	spriteRect.bottom = texHeight;
}
//function renders the normal nontransparent image
void Sprite::BlitSpr(BYTE *destination, unsigned int destWdth, unsigned int PosX, unsigned int PosY)
{
	BYTE *destPntr = destination + (PosX + PosY*destWdth) * 4;

	BYTE *sourcePntr = textureData;


	for (unsigned int y = 0; y < texHeight; y++)
	{
		memcpy(destPntr, sourcePntr, texWidth * 4);

		sourcePntr += texWidth * 4;

		destPntr += destWdth * 4;

	}

}


void Sprite::ClipBlit(BYTE *destination, unsigned int destWdth, int PosX, int PosY, unsigned int destHeight, int framewidth, int frameheight, int framenumber)
{
	// creates the two rectangles to clip

	ClippedRect.left = 0;
	ClippedRect.right = framewidth;
	ClippedRect.top = 0;
	ClippedRect.bottom = frameheight;

	//sets the dest rectangle the screen size
	destRect.left = 0;
	destRect.right = destWdth;
	destRect.top = 0;
	destRect.bottom = destHeight;


	//sets the clipping rectangle to the sprite size
	ClippedRect.Translate(PosX, PosY);


	//checks to see if the clipping rectangle is outside of the screen
	if (ClippedRect.OutsideOf(destRect))
	{
		return;
	}

	//clips the clipping rectangle to the size of the screen rectangle
	ClippedRect.ClipTo(destRect);

	//removes the positions of the sprite
	ClippedRect.Translate(-PosX, -PosY);

	ClippedRect.Translate(framenumber * framewidth, 0);

	FrameRect = ClippedRect;
	//clamps the positions
	if (PosX < 0)
	{
		PosX = 0;
	}
	if (PosY < 0)
	{
		PosY = 0;
	}
	//destination pointer
	BYTE *destPntr = destination + (PosX + PosY * destWdth) * 4;
	//source pointer for the sprite
	BYTE *sourcePntr = textureData + (ClippedRect.left + ClippedRect.top * ClippedRect.GetWidth()) * 4;

	int endOflineDestinc = (destWdth - ClippedRect.GetWidth()) * 4;
	int endOflineSourceinc = (texWidth - ClippedRect.GetWidth()) * 4;

	//if the clipping rectangle is partially in the screen renders only part of the image
	if (destRect.Contains(ClippedRect))
	{
		for (unsigned int y = 0; y < ClippedRect.GetHeight(); y++)
		{
			for (unsigned int x = 0; x < ClippedRect.GetWidth(); x++)
			{
				BYTE alpha = sourcePntr[3];

				if (alpha == 255)
				{
					memcpy(destPntr, sourcePntr, 4);
				}
				// if alpha = 255 then set mask to 1 >>> mask needs creating here or in VIZ 
				// the mask is then checked against anohter mask to see if the 1's hit each other!!!!
				// then you add the offset it seems to see what row of the image you are on to check?

				//see if any transparency with alpha spo if alpha = 0 then full transparent, alpha = 255 then full opaque
				else if (alpha == 0)
				{
					destPntr[0] = destPntr[0];
					destPntr[1] = destPntr[1];
					destPntr[2] = destPntr[2];
				}
				else
				{
					BYTE blue = sourcePntr[0];
					BYTE green = sourcePntr[1];
					BYTE red = sourcePntr[2];

					destPntr[0] = destPntr[0] + ((alpha*(blue - destPntr[0])) >> 8);
					destPntr[1] = destPntr[1] + ((alpha*(green - destPntr[1])) >> 8);
					destPntr[2] = destPntr[2] + ((alpha*(red - destPntr[2])) >> 8);
				}
				destPntr += 4;
				sourcePntr += 4;
			}
			//increments the pointers
			destPntr += endOflineDestinc;
			sourcePntr += endOflineSourceinc;
		}

	}

}
