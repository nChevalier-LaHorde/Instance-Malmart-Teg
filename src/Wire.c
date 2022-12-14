#include "Wire.h"
#include "components/spritecomponent.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <h3/ui.h>

typedef struct
{
	float px;
	float py;
	int nbr;
	int WireCount;
	int GameOver;
	int wireRnd;
	int pos1;
	int pos2;
	int pos3;
	int pos4;
	bool wireOn;
	bool resolved;
	bool wireCreate;
	bool WirePlug;
	H3Handle Wire;
	H3Handle Wire1;
	H3Handle Wire2;
	H3Handle Wire3;
	H3Handle Wire4;
	H3Handle scene;
	H3Handle Player;
	H3Handle WirePlugText;
} WireComponent_Properties;

void WireComponent_Terminate(void* properties)
{
	free(properties);
}

void WireComponent_Update(H3Handle h3, H3Handle object, SH3Transform* transform, float t, float dt, void* properties)
{
	WireComponent_Properties* props = (WireComponent_Properties*)properties;

	H3_Transform_GetPosition(H3_Object_GetTransform(props->Player), &props->px, &props->py);

	if (props->wireCreate == true)
	{
		props->Wire = H3_Object_Create2(props->scene, "Wire", NULL, 11);
		H3_Object_SetTranslation(props->Wire, 2995, 90);
		props->wireCreate = false;
	}

	if (H3_Ui_BeginWindow("Wire"))
	{
		H3_Ui_Printf("wireRnd: %d", props->wireRnd);
	}
	H3_Ui_EndWindow();

	if (props->resolved == false)
	{

		if (H3_Input_IsKeyPressed(K_Space))
		{
			if (2990 < props->px && props->px < 3000 && 90>props->py && props->py > 85)
			{
				H3_Object_AddComponent(props->Wire, SPRITECOMPONENT_CREATE("assets/wires/wires0.png", A_Center + A_Middle));
				props->wireOn = true;
			}
		}
		else if (props->py > 90)
		{
			props->wireOn = false;
			H3_Object_Destroy(props->Wire, false);
			props->wireCreate = true;
		}

		if (props->wireOn == true)
		{
			H3_Object_SetTranslation(props->Player, 2995, 88);
			if (props->wireRnd = 1)
			{
				if (props->pos1 == 2)
				{
					H3_Object_AddComponent(props->Wire1, SPRITECOMPONENT_CREATE("assets/wires/wiresPos/yellow1.png", A_Middle + A_Center));
				}
			}
		}

		if (props->GameOver == 1)
		{
			//ACCESSOR isCatch
			if (H3_Ui_BeginWindow("Wire"))
			{
				H3_Ui_Printf("GameOver = true");
			}
			H3_Ui_EndWindow();
		}

	}
}

	//2990 a 3000

void WireComponent_Draw(H3Handle h3, SH3Transform* transform, void* properties)
{
	WireComponent_Properties* props = (WireComponent_Properties*)properties;

	if (props->wireOn == true)
	{
		if (H3_Button(h3, props->WirePlugText, 720, 203, A_Center + A_Middle))
		{
			if (props->wireRnd == 1)
			{
				props->pos1 += 1;
			}	
			if (props->wireRnd == 2)
			{
				props->pos2 += 1;
			}
			if (props->wireRnd == 3)
			{
				props->pos3 += 1;
			}
			if (props->wireRnd == 4)
			{
				props->pos4 += 1;
			}
		}
		if (H3_Button(h3, props->WirePlugText, 720, 364, A_Center + A_Middle))
		{
			if (props->wireRnd == 1)
			{
				props->pos1 += 2;
			}
			if (props->wireRnd == 2)
			{
				props->pos2 += 2;
			}
			if (props->wireRnd == 3)
			{
				props->pos3 += 2;
			}
			if (props->wireRnd == 4)
			{
				props->pos4 += 2;
			}
		}
		if (H3_Button(h3, props->WirePlugText, 720, 524, A_Center + A_Middle))
		{
			if (props->wireRnd == 1)
			{
				props->pos1 += 4;
			}
			if (props->wireRnd == 2)
			{
				props->pos2 += 4;
			}
			if (props->wireRnd == 3)
			{
				props->pos3 += 4;
			}
			if (props->wireRnd == 4)
			{
				props->pos4 +=4;
			}
		}
		if (H3_Button(h3, props->WirePlugText, 720, 682, A_Center + A_Middle))
		{
			if (props->wireRnd == 1)
			{
				props->pos1 += 8;
			}
			if (props->wireRnd == 2)
			{
				props->pos2 += 8;
			}
			if (props->wireRnd == 3)
			{
				props->pos3 += 8;
			}
			if (props->wireRnd == 4)
			{
				props->pos4 += 8;
			};
		}
		if (H3_Button(h3, props->WirePlugText, 1120, 203, A_Center + A_Middle))
		{
			if (props->wireRnd == 1)
			{
				props->pos1 += 1;
			}
			if (props->wireRnd == 2)
			{
				props->pos2 += 1;
			}
			if (props->wireRnd == 3)
			{
				props->pos3 += 4;
			}
			if (props->wireRnd == 4)
			{
				props->pos4 += 2;
			}
		}
		if (H3_Button(h3, props->WirePlugText, 1120, 364, A_Center + A_Middle))
		{
			if (props->wireRnd == 1)
			{
				props->pos1 += 4;
			}
			if (props->wireRnd == 2)
			{
				props->pos2 += 8;
			}
			if (props->wireRnd == 3)
			{
				props->pos3 += 2;
			}
			if (props->wireRnd == 4)
			{
				props->pos4 += 1;
			}
		}
		if (H3_Button(h3, props->WirePlugText, 1120, 524, A_Center + A_Middle))
		{
			if (props->wireRnd == 1)
			{
				props->pos1 += 2;
			}
			if (props->wireRnd == 2)
			{
				props->pos2 += 8;
			}
			if (props->wireRnd == 3)
			{
				props->pos3 += 8;
			}
			if (props->wireRnd == 4)
			{
				props->pos4 += 4;
			}
		}
		if (H3_Button(h3, props->WirePlugText, 1120, 682, A_Center + A_Middle))
		{
			if (props->wireRnd == 1)
			{
				props->pos1 += 8;
			}
			if (props->wireRnd == 2)
			{
				props->pos2 += 2;
			}
			if (props->wireRnd == 3)
			{
				props->pos3 += 1;
			}
			if (props->wireRnd == 4)
			{
				props->pos4 += 8;
			}
		}

	}
}

void* WireComponent_CreateProperties(H3Handle scene, H3Handle Player)
{
	WireComponent_Properties* properties = malloc(sizeof(WireComponent_Properties));
	H3_ASSERT_CONSOLE(properties, "Failed to allocate properties");

	properties->scene = scene;
	properties->Player = Player;

	properties->wireRnd = (rand() % 4) + 1;
	properties->pos1 = 0;
	properties->pos2 = 0;
	properties->pos3 = 0;
	properties->pos4 = 0;

	properties->resolved = false;
	properties->wireOn = false;
	properties->wireCreate = true;
	properties->WirePlug = false;

	properties->Wire1 = H3_Object_Create2(properties->scene, "Wire1", NULL, 12);
	properties->Wire2 = H3_Object_Create2(properties->scene, "Wire2", NULL, 12);
	properties->Wire3 = H3_Object_Create2(properties->scene, "Wire3", NULL, 12);
	properties->Wire4 = H3_Object_Create2(properties->scene, "Wire4", NULL, 12);

	int wiw, wih;
	properties->WirePlugText = H3_Texture_Load("assets/wires/wire_plug.png", &wiw, &wih);

	return properties;
}