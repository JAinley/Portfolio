#include "WorldEntityPlayer.h"
#include "WorldEntity.h"
#include <HAPI_lib.h>
#include <HAPI_InputCodes.h>
#include "Visuals.h"
#include "Sprite.h"


WorldEntityPlayer::WorldEntityPlayer()
{
}


WorldEntityPlayer::~WorldEntityPlayer()
{
}

void WorldEntityPlayer::Movement()
{
	//this function gets all input data and correlates it to movement for the player entity only

	bool SetControllerRumble(unsigned int controller, WORD LeftMotor, WORD RightMotor);

	//gets the controller information for input
	for (unsigned int i = 0; i < HAPI.GetMaxControllers(); i++) {
		const HAPI_TKeyboardData& KeyData = HAPI.GetKeyboardData();
		const HAPI_TControllerData& Controller = HAPI.GetControllerData(i);
		if (Controller.isAttached)
		{
			WORD LeftMotor = 0;
			WORD RightMotor = 0;

			int x = Controller.analogueButtons[HK_ANALOGUE_LEFT_THUMB_X];
			int y = Controller.analogueButtons[HK_ANALOGUE_LEFT_THUMB_Y];

			int MaxMotor = 65535;
			if (Controller.digitalButtons[HK_DIGITAL_A])
			{
				WORD LeftMotor = MaxMotor;
				WORD RightMotor = MaxMotor;
				HAPI.SetControllerRumble(0, LeftMotor, RightMotor);
			}
			else
			{
				WORD LeftMotor = 0;
				WORD RightMotor = 0;
				HAPI.SetControllerRumble(0, LeftMotor, RightMotor);
			}


			if (Controller.digitalButtons[HK_DIGITAL_DPAD_DOWN])
			{
				PosY++;
			}
			else if (Controller.digitalButtons[HK_DIGITAL_DPAD_UP])
			{
				PosY--;
			}
			else if (Controller.digitalButtons[HK_DIGITAL_DPAD_LEFT] || KeyData.scanCode['A'])
			{
				direction = 2;
				//HAPI.PlayStreamedMedia("Data\\Running_01.mp3");
				PosX -= PlayerSpeed;
				WorldPosX -= PlayerSpeed;
				running = anim::two;
			}
			else if (Controller.digitalButtons[HK_DIGITAL_DPAD_RIGHT] || KeyData.scanCode['D'])
			{
				direction = 1;
				//HAPI.PlaySound("Data\\Running_01.wav");
				PosX += PlayerSpeed;
				WorldPosX += PlayerSpeed;
				running = anim::one;
			}
			else
			{
				running = anim::three;
			}
			return;
		}
	}


}


