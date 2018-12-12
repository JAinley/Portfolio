/*
	HAPI Start
	----------
	This solution contains an already set up HAPI project and this main file

	The directory structure and main files are:

	HAPI_Start - contains the Visual Studio solution file (.sln)
		HAPI_APP - contains the Visual Studio HAPI_APP project file (.vcxproj) and source code
			HAPI - the directory with all the HAPI library files
*/

// Include the HAPI header to get access to all of HAPIs interfaces
#include <HAPI_lib.h>
#include <HAPI_InputCodes.h>
#include "Visuals.h"
#include "Sprite.h"
#include "WorldModel.h"


// HAPI itself is wrapped in the HAPISPACE namespace
using namespace HAPISPACE;

WorldModel *World = new WorldModel();
// Every HAPI program has a HAPI_Main as an entry point
// When this function exits the program will close down
void HAPI_Main()
{
	if (World->LoadWorld() == true)
	{

		HAPI.PlayStreamedMedia("Data\\GameMusic.mp3");
		while (HAPI.Update())
		{
			World->Run();
		}

	}
	else
	{
		return;
	}
	delete World;

}
