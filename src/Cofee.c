#include "Cofee.h"
#include "components/spritecomponent.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include <h3/ui.h>

#include <components/playercomponent.h>

typedef struct
{
	float px;
	float py;
	int brx;
	int bry;
	int bbx;
	int bby;
	int brox;
	int broy;
	int bjx;
	int bjy;
	int mx;
	int my;
	int buttonBlueNbr;
	int buttonYellowNbr;
	int buttonRedNbr;
	int buttonPinkNbr;
	int ButtonCount;
	int nbr;
	int GameOver;
	bool resolved;
	bool buttonOn; 
	bool buttonCreate;
	bool ButtonBlue;
	bool ButtonRed;
	bool ButtonYellow;
	bool ButtonPink;
	bool bbp;
	bool brp;
	bool byp;
	bool bpp;
	H3Handle Button;
	H3Handle Player;
	H3Handle scene;
	H3Handle ButtonRedPressed;
	H3Handle ButtonPinkPressed;
	H3Handle ButtonYellowPressed;
	H3Handle ButtonBluePressed;
	H3Handle buttonBlueTex;
	H3Handle buttonRedTex;
	H3Handle buttonPinkTex;
	H3Handle buttonYellowTex;
} CofeeComponent_Properties;

void CofeeComponent_Terminate(void* properties)
{
	free(properties);
}

void CofeeComponent_Update(H3Handle h3, H3Handle object, SH3Transform* transform, float t, float dt, void* properties)
{
	CofeeComponent_Properties* props = (CofeeComponent_Properties*)properties;

	H3_Transform_GetPosition(H3_Object_GetTransform(props->Player), &props->px, &props->py);
	H3_Input_GetMousePos(h3, &props->mx, &props->my);

	/*if (H3_Ui_BeginWindow("Coffee"))
	{
		H3_Ui_Printf("position = (%d, %d)", props->mx, props->my);
	}
	H3_Ui_EndWindow();*/



	if (props->buttonCreate == true)
	{
 		props->Button = H3_Object_Create2(props->scene, "Button", NULL, 11);
		H3_Object_SetTranslation(props->Button, 2200, 313);
		props->buttonCreate = false;
	}

	if (props->resolved == false)
	{
		/*if (H3_Ui_BeginWindow("Coffee"))
		{
			H3_Ui_Printf("nbr = %d", props->nbr);
		}
		H3_Ui_EndWindow();*/

		props->nbr = 0;

		/*if (H3_Ui_BeginWindow("Coffee"))
		{
			H3_Ui_Printf("Count = %d", props->ButtonCount);
		}
		H3_Ui_EndWindow();*/

		/*if (H3_Ui_BeginWindow("Coffee"))
		{
			H3_Ui_Printf("GameOver = %d", props->GameOver);
		}
		H3_Ui_EndWindow();*/

		if (H3_Input_IsKeyPressed(K_Space))
		{


			if (2180 < props->px && props->px < 2226 && 320>props->py && props->py > 316)
			{
				H3_Object_AddComponent(props->Button, SPRITECOMPONENT_CREATE("assets/buttons/buttons.png", A_Center + A_Middle));
				props->buttonOn = true;
			}
		}
		else if (props->py > 318)
		{
			props->buttonOn = false;
			H3_Object_Destroy(props->Button, false);
			props->buttonCreate = true;
			H3_Object_RemoveComponent(props->ButtonRedPressed, SPRITECOMPONENT_TYPEID);
			H3_Object_RemoveComponent(props->ButtonBluePressed, SPRITECOMPONENT_TYPEID);
			H3_Object_RemoveComponent(props->ButtonPinkPressed, SPRITECOMPONENT_TYPEID);
			H3_Object_RemoveComponent(props->ButtonYellowPressed, SPRITECOMPONENT_TYPEID);
		}

		if (props->buttonOn == true)
		{
			/*if (H3_Ui_BeginWindow("Coffee"))
			{
				H3_Ui_Printf("buttonOn = true", props->buttonOn);
			}
			H3_Ui_EndWindow();*/

			H3_Object_SetTranslation(props->Player, 2205, 316);

			if (props->ButtonBlue == true)
			{
				H3_Object_AddComponent(props->ButtonBluePressed, SPRITECOMPONENT_CREATE("assets/buttons/bluepressed.png", A_Center + A_Middle));
				H3_Object_SetTranslation(props->ButtonBluePressed, props->px - 45, props->py-4);
				props->ButtonCount += 1;
				if (props->ButtonCount == 1)
				{
					props->buttonBlueNbr = 5;
				}
				else
				{
					props->buttonBlueNbr = 6;
				}
				props->ButtonBlue = false;
				props->bbp = true;
			}
			if (props->ButtonPink == true)
			{
				H3_Object_AddComponent(props->ButtonPinkPressed, SPRITECOMPONENT_CREATE("assets/buttons/pinkpressed.png", A_Center + A_Middle));
				H3_Object_SetTranslation(props->ButtonPinkPressed, props->px + 35, props->py - 4);
				props->ButtonCount += 1;
				if (props->ButtonCount == 3)
				{
					props->buttonPinkNbr = 5;
				}
				else
				{
					props->buttonPinkNbr = 6;
				}
				props->ButtonPink = false;
				props->bpp = true;
			}
			if (props->ButtonRed == true)
			{
				H3_Object_AddComponent(props->ButtonRedPressed, SPRITECOMPONENT_CREATE("assets/buttons/redpressed.png", A_Center + A_Middle));
				H3_Object_SetTranslation(props->ButtonRedPressed, props->px - 125, props->py - 4);
				props->ButtonCount += 1;
				if (props->ButtonCount == 2)
				{
					props->buttonRedNbr = 5;
				}
				else
				{
					props->buttonRedNbr = 6;
				}
				props->ButtonRed = false;
				props->brp = true;
			}
			if (props->ButtonYellow == true)
			{
				H3_Object_AddComponent(props->ButtonYellowPressed, SPRITECOMPONENT_CREATE("assets/buttons/yellowpressed.png", A_Center + A_Middle));
				H3_Object_SetTranslation(props->ButtonYellowPressed, props->px + 115, props->py - 4);
				props->ButtonCount += 1;
				if (props->ButtonCount == 4)
				{
					props->buttonYellowNbr = 5;
				}
				else
				{
					props->buttonYellowNbr = 6;
				}
				props->ButtonYellow = false;
				props->byp = true;
			}
			props->nbr = props->buttonBlueNbr + props->buttonRedNbr + props->buttonPinkNbr + props->buttonYellowNbr;

			if (props->bbp == true && props->brp == true && props->byp == true && props->bpp == true)
			{
				if (props->nbr == 20)
				{
					props->resolved = true;
					props->buttonRedNbr = 0;
					props->buttonPinkNbr = 0;
					props->buttonBlueNbr = 0;
					props->buttonYellowNbr = 0;
					props->buttonOn = false;
					H3_Object_Destroy(props->Button, false);
					props->buttonCreate = false;
					H3_Object_RemoveComponent(props->ButtonRedPressed, SPRITECOMPONENT_TYPEID);
					H3_Object_RemoveComponent(props->ButtonBluePressed, SPRITECOMPONENT_TYPEID);
					H3_Object_RemoveComponent(props->ButtonPinkPressed, SPRITECOMPONENT_TYPEID);
					H3_Object_RemoveComponent(props->ButtonYellowPressed, SPRITECOMPONENT_TYPEID);
				}
				else
				{
					props->GameOver += 1;
					H3_Object_SetTranslation(props->Player, 2205, 315);
					props->byp = false;
					props->bbp = false;
					props->bpp = false;
					props->brp = false;
					props->buttonRedNbr = 0;
					props->buttonPinkNbr = 0;
					props->buttonBlueNbr = 0;
					props->buttonYellowNbr = 0;
					props->ButtonCount = 0;

				}
			}
		}
		
		if (props->GameOver == 3)
		{
			PlayerComponent_SetisCatchEx(props->Player, true);
			/*if (H3_Ui_BeginWindow("Coffee"))
			{
				H3_Ui_Printf("GameOver = true");
			}
			H3_Ui_EndWindow();*/
		}

	}
}

void CofeeComponent_Draw(H3Handle h3, SH3Transform* transform, void* properties)
{
	CofeeComponent_Properties* props = (CofeeComponent_Properties*)properties;

	if (props->buttonOn == true)
	{
		if (H3_Button(h3, props->buttonBlueTex, 817, 480, A_Center + A_Middle))
		{
			props->ButtonBlue = true;			
		}
		if (H3_Button(h3, props->buttonRedTex, 658, 480, A_Center + A_Middle))
		{
			props->ButtonRed = true;
		}
		if (H3_Button(h3, props->buttonPinkTex, 978, 480, A_Center + A_Middle))
		{
			props->ButtonPink = true;

		}
		if (H3_Button(h3, props->buttonYellowTex, 1138, 480, A_Center + A_Middle))
		{
			props->ButtonYellow = true;
		}
	}
}

void* CofeeComponent_CreateProperties(H3Handle scene, H3Handle Player)
{
	CofeeComponent_Properties* properties = malloc(sizeof(CofeeComponent_Properties));
	H3_ASSERT_CONSOLE(properties, "Failed to allocate properties");

	properties->buttonCreate = true;
	properties->Player = Player;
	properties->scene = scene;
	properties->resolved = false;
	properties->buttonOn = false;
	properties->ButtonBlue = false;
	properties->ButtonRed = false;
	properties->ButtonPink = false;
	properties->ButtonYellow = false;
	properties->ButtonRedPressed = H3_Object_Create2(properties->scene, "ButtonRedPressed", NULL, 13);
	properties->ButtonPinkPressed = H3_Object_Create2(properties->scene, "ButtonPinkPressed", NULL, 13);
	properties->ButtonYellowPressed = H3_Object_Create2(properties->scene, "ButtonYellowPressed", NULL, 13);
	properties->ButtonBluePressed = H3_Object_Create2(properties->scene, "ButtonBluePressed", NULL, 13);
	properties->bbp = false;
	properties->brp = false;
	properties->byp = false;
	properties->bpp = false;
	properties->GameOver = 0;

	properties->nbr = 0;
	properties->ButtonCount = 0;
	properties->buttonYellowNbr = 0;
	properties->buttonBlueNbr = 0;
	properties->buttonRedNbr = 0;
	properties->buttonPinkNbr = 0;

	int bbtw, bbth;
	properties->buttonBlueTex = H3_Texture_Load("assets/buttons/blue_button.png", &bbtw, &bbth);

	int bytw, byth;
	properties->buttonRedTex = H3_Texture_Load("assets/buttons/red_button.png", &bytw, &byth);

	int bptw, bpth;
	properties->buttonPinkTex = H3_Texture_Load("assets/buttons/pink_button.png", &bptw, &bpth);

	int brtw, brth;
	properties->buttonYellowTex = H3_Texture_Load("assets/buttons/yellow_button.png", &brtw, &brth);

	return properties;
}