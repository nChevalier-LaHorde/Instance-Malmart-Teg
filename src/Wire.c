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
	float wx;
	float wy;
	bool wireOn;
	bool WireResolved;
	bool wireCreate;
	bool WirePlug;
	bool alreadyplaced1;
	bool alreadyplaced2;
	bool alreadyplaced3;
	bool alreadyplaced4;
	bool place1;
	bool place2;
	bool place3;
	bool place4;
	H3Handle Wire;
	H3Handle Wire1;
	H3Handle Wire2;
	H3Handle Wire3;
	H3Handle Wire4;
	H3Handle scene;
	H3Handle Player;
	H3Handle WirePlugText;
	H3Handle PlugUsed1;
	H3Handle PlugUsed2;
	H3Handle PlugUsed3;
	H3Handle PlugUsed4;
	H3Handle PlugUsed5;
	H3Handle PlugUsed6;
	H3Handle PlugUsed7;
	H3Handle PlugUsed8;
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

	H3_Transform_GetPosition(H3_Object_GetTransform(props->Wire1), &props->wx, &props->wy);

	if (H3_Ui_BeginWindow("Wire"))
	{
		H3_Ui_Printf("wireRnd: %d", props->wireRnd);
	}
	H3_Ui_EndWindow();
	

	if (props->WireResolved == false)
	{

		if (H3_Input_IsKeyPressed(K_Space))
		{
			if (2990 < props->px && props->px < 3000 && 98>props->py && props->py > 92)
			{
				H3_Object_AddComponent(props->Wire, SPRITECOMPONENT_CREATE("assets/wires/wires0.png", A_Center + A_Middle));
				props->wireOn = true;
			}
		}
		else if (props->py > 94)
		{
			props->wireOn = false;
			H3_Object_Destroy(props->Wire, false);
			props->wireCreate = true;
			props->pos1 = 0;
			props->pos2 = 0;
			props->pos3 = 0;
			props->pos4 = 0;
		}

		if (props->wireOn == false)
		{
			H3_Object_RemoveComponent(props->Wire1, SPRITECOMPONENT_TYPEID);
			H3_Object_RemoveComponent(props->Wire2, SPRITECOMPONENT_TYPEID);
			H3_Object_RemoveComponent(props->Wire3, SPRITECOMPONENT_TYPEID);
			H3_Object_RemoveComponent(props->Wire4, SPRITECOMPONENT_TYPEID);
			H3_Object_RemoveComponent(props->PlugUsed1, SPRITECOMPONENT_TYPEID);
			H3_Object_RemoveComponent(props->PlugUsed2, SPRITECOMPONENT_TYPEID);
			H3_Object_RemoveComponent(props->PlugUsed3, SPRITECOMPONENT_TYPEID);
			H3_Object_RemoveComponent(props->PlugUsed4, SPRITECOMPONENT_TYPEID);
			H3_Object_RemoveComponent(props->PlugUsed5, SPRITECOMPONENT_TYPEID);
			H3_Object_RemoveComponent(props->PlugUsed6, SPRITECOMPONENT_TYPEID);
			H3_Object_RemoveComponent(props->PlugUsed7, SPRITECOMPONENT_TYPEID);
			H3_Object_RemoveComponent(props->PlugUsed8, SPRITECOMPONENT_TYPEID);
		}

		

		if (props->wireOn == true)
		{
			H3_Object_SetTranslation(props->Player, 2995, 92);

			if (props->wireRnd == 1)
			{
				if (props->alreadyplaced1 == false)
				{
					if (props->pos1 == 2)
					{
						H3_Object_AddComponent(props->Wire1, SPRITECOMPONENT_CREATE("assets/wires/wiresPos/yellow1.png", A_Middle + A_Center));
						H3_Object_SetTranslation(props->Wire1, 2995, -31);
						props->alreadyplaced1 = true;
						props->place1 = true;
						props->pos1 = 0;
					}
				}
				if (props->alreadyplaced2 == false)
				{
					if (props->pos1 == 20)
					{
						H3_Object_AddComponent(props->Wire2, SPRITECOMPONENT_CREATE("assets/wires/wiresPos/pink3.png", A_Top + A_Left));
						H3_Object_SetTranslation(props->Wire2, 2888, 43);
						props->alreadyplaced2 = true;
						props->place2 = true;
						props->pos1 = 0;
					}
				}
				if (props->alreadyplaced3 == false)
				{
					if (props->pos1 == 200)
					{
						H3_Object_AddComponent(props->Wire3, SPRITECOMPONENT_CREATE("assets/wires/wiresPos/blue2.png", A_Top + A_Left));
						H3_Object_SetTranslation(props->Wire3, 2888, 43);
						props->alreadyplaced3 = true;
						props->place3 = true;
						props->pos1 = 0;
					}
				}
				if (props->alreadyplaced4 == false)
				{
					if (props->pos1 == 2000)
					{
						H3_Object_AddComponent(props->Wire4, SPRITECOMPONENT_CREATE("assets/wires/wiresPos/red4.png", A_Top + A_Left));
						H3_Object_SetTranslation(props->Wire4, 2888, 203);
						props->alreadyplaced4 = true;
						props->place4 = true;
						props->pos1 = 0;
					}
				}
				if (props->place1 == true && props->place2 == true && props->place3 == true && props->place4 == true)
				{
					props->WireResolved = true;
				}
			}
			if (props->wireRnd == 2)
			{
				if (props->alreadyplaced1 == false)
				{
					if (props->pos2 == 2)
					{
						H3_Object_AddComponent(props->Wire1, SPRITECOMPONENT_CREATE("assets/wires/wiresPos/yellow1.png", A_Middle + A_Center));
						H3_Object_SetTranslation(props->Wire1, 2995, -31);
						props->alreadyplaced1 = true;
						props->place1 = true;
						props->pos2 = 0;
					}
				}
				if (props->alreadyplaced2 == false)
				{
					if (props->pos2 == 20)
					{
						H3_Object_AddComponent(props->Wire2, SPRITECOMPONENT_CREATE("assets/wires/wiresPos/pink3.png", A_Middle + A_Center));
						H3_Object_SetTranslation(props->Wire2, 2995, 90);
						props->alreadyplaced2 = true;
						props->place2 = true;
						props->pos2 = 0;
					}
				}
				if (props->alreadyplaced3 == false)
				{
					if (props->pos2 == 200)
					{
						H3_Object_AddComponent(props->Wire3, SPRITECOMPONENT_CREATE("assets/wires/wiresPos/blue4.png", A_Middle + A_Center));
						H3_Object_SetTranslation(props->Wire3, 2995, 170);
						props->alreadyplaced3 = true;
						props->place3 = true;
						props->pos2 = 0;
					}
				}
				if (props->alreadyplaced4 == false)
				{
					if (props->pos2 == 2000)
					{
						H3_Object_AddComponent(props->Wire4, SPRITECOMPONENT_CREATE("assets/wires/wiresPos/red2.png", A_Middle + A_Center));
						H3_Object_SetTranslation(props->Wire4, 2995, 130);
						props->alreadyplaced4 = true;
						props->place4 = true;
						props->pos2 = 0;
					}
				}
			}
			if (props->wireRnd == 3)
			{
				if (props->alreadyplaced1 == false)
				{
					if (props->pos3 == 2)
					{
						H3_Object_AddComponent(props->Wire1, SPRITECOMPONENT_CREATE("assets/wires/wiresPos/yellow4.png", A_Middle + A_Center));
						H3_Object_SetTranslation(props->Wire1, 2995, 90);
						props->alreadyplaced1 = true;
						props->place1 = true;
						props->pos3 = 0;
					}
				}
				if (props->alreadyplaced2 == false)
				{
					if (props->pos3 == 20)
					{
						H3_Object_AddComponent(props->Wire2, SPRITECOMPONENT_CREATE("assets/wires/wiresPos/pink2.png", A_Middle + A_Center));
						H3_Object_SetTranslation(props->Wire2, 2995, 50);
						props->alreadyplaced2 = true;
						props->place2 = true;
						props->pos3 = 0;
					}
				}
				if (props->alreadyplaced3 == false)
				{
					if (props->pos3 == 200)
					{
						H3_Object_AddComponent(props->Wire3, SPRITECOMPONENT_CREATE("assets/wires/wiresPos/blue1.png", A_Middle + A_Center));
						H3_Object_SetTranslation(props->Wire3, 2995, 50);
						props->alreadyplaced3 = true;
						props->place3 = true;
						props->pos3 = 0;
					}
				}
				if (props->alreadyplaced4 == false)
				{
					if (props->pos3 == 2000)
					{
						H3_Object_AddComponent(props->Wire4, SPRITECOMPONENT_CREATE("assets/wires/wiresPos/red3.png", A_Middle + A_Center));
						H3_Object_SetTranslation(props->Wire4, 2995, 170);
						props->alreadyplaced4 = true;
						props->place4 = true;
						props->pos3 = 0;
					}
				}
			}
			if (props->wireRnd == 4)
			{
				if (props->alreadyplaced1 == false)
				{
					if (props->pos4 == 2)
					{
						H3_Object_AddComponent(props->Wire1, SPRITECOMPONENT_CREATE("assets/wires/wiresPos/yellow2.png", A_Middle + A_Center));
						H3_Object_SetTranslation(props->Wire1, 2995, 10);
						props->alreadyplaced1 = true;
						props->place1 = true;
						props->pos4 = 0;
					}
				}
				if (props->alreadyplaced2 == false)
				{
					if (props->pos4 == 20)
					{
						H3_Object_AddComponent(props->Wire2, SPRITECOMPONENT_CREATE("assets/wires/wiresPos/pink1.png", A_Middle + A_Center));
						H3_Object_SetTranslation(props->Wire2, 2995, 10);
						props->alreadyplaced2 = true;
						props->place2 = true;
						props->pos4 = 0;
					}
				}
				if (props->alreadyplaced3 == false)
				{
					if (props->pos4 == 200)
					{
						H3_Object_AddComponent(props->Wire3, SPRITECOMPONENT_CREATE("assets/wires/wiresPos/blue3.png", A_Middle + A_Center));
						H3_Object_SetTranslation(props->Wire3, 2995, 130);
						props->alreadyplaced3 = true;
						props->place3 = true;
						props->pos4 = 0;
					}
				}
				if (props->alreadyplaced4 == false)
				{
					if (props->pos4 == 2000)
					{
						H3_Object_AddComponent(props->Wire4, SPRITECOMPONENT_CREATE("assets/wires/wiresPos/red4.png", A_Middle + A_Center));
						H3_Object_SetTranslation(props->Wire4, 2995, 210);
						props->alreadyplaced4 = true;
						props->place4 = true;
						props->pos4 = 0;
					}
				}
			}
		}

		if (props->place1 == true && props->place2 == true && props->place3 == true && props->place4 == true)
		{
			props->WireResolved = true;
			props->wireCreate = false;
			props->wireOn = false;
			H3_Object_Destroy(props->Wire, false);
			H3_Object_SetTranslation(props->Player, 2995, 100);
			H3_Object_RemoveComponent(props->Wire1, SPRITECOMPONENT_TYPEID);
			H3_Object_RemoveComponent(props->Wire2, SPRITECOMPONENT_TYPEID);
			H3_Object_RemoveComponent(props->Wire3, SPRITECOMPONENT_TYPEID);
			H3_Object_RemoveComponent(props->Wire4, SPRITECOMPONENT_TYPEID);
			H3_Object_RemoveComponent(props->PlugUsed1, SPRITECOMPONENT_TYPEID);
			H3_Object_RemoveComponent(props->PlugUsed2, SPRITECOMPONENT_TYPEID);
			H3_Object_RemoveComponent(props->PlugUsed3, SPRITECOMPONENT_TYPEID);
			H3_Object_RemoveComponent(props->PlugUsed4, SPRITECOMPONENT_TYPEID);
			H3_Object_RemoveComponent(props->PlugUsed5, SPRITECOMPONENT_TYPEID);
			H3_Object_RemoveComponent(props->PlugUsed6, SPRITECOMPONENT_TYPEID);
			H3_Object_RemoveComponent(props->PlugUsed7, SPRITECOMPONENT_TYPEID);
			H3_Object_RemoveComponent(props->PlugUsed8, SPRITECOMPONENT_TYPEID);
		}

		if (props->pos1 !=0 && props->pos1 != 1 && props->pos1 != 2 && props->pos1 != 10 && props->pos1 != 20 && props->pos1 != 100 && props->pos1 != 200 && props->pos1 != 1000 && props->pos1 != 2000)
		{
			props->GameOver = 1;
		}
		if (props->pos2 != 0 && props->pos2 != 1 && props->pos2 != 2 && props->pos2 != 10 && props->pos2 != 20 && props->pos2 != 100 && props->pos2 != 200 && props->pos2 != 1000 & props->pos2 != 2000)
		{
			props->GameOver = 1;
		}
		if (props->pos3 != 0 && props->pos3 != 1 && props->pos3 != 2 && props->pos3 != 10 && props->pos3 != 20 && props->pos3 != 100 && props->pos3 != 200 && props->pos3 != 1000 && props->pos3 != 2000)
		{
			props->GameOver = 1;
		}
		if (props->pos4 != 0 && props->pos4 != 1 && props->pos4 != 2 && props->pos4 != 10 && props->pos4 != 20 && props->pos4 != 100 && props->pos4 != 200 && props->pos4 != 1000 && props->pos4 != 2000)
		{
			props->GameOver = 1;
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

	
void WireComponent_Draw(H3Handle h3, SH3Transform* transform, void* properties)
{
	WireComponent_Properties* props = (WireComponent_Properties*)properties;

	if (props->wireOn == true)
	{
		if (H3_Button(h3, props->WirePlugText, 720, 255, A_Center + A_Middle))
		{
			H3_Object_SetTranslation(props->PlugUsed1, 2895, -31);
			H3_Object_AddComponent(props->PlugUsed1, SPRITECOMPONENT_CREATE("assets/wires/wire_plug_used.png", A_Middle + A_Center));
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
		if (H3_Button(h3, props->WirePlugText, 720, 416, A_Center + A_Middle))
		{
			H3_Object_SetTranslation(props->PlugUsed2, 2895, 50);
			H3_Object_AddComponent(props->PlugUsed2, SPRITECOMPONENT_CREATE("assets/wires/wire_plug_used.png", A_Middle + A_Center));
			if (props->wireRnd == 1)
			{
				props->pos1 += 10;
			}
			if (props->wireRnd == 2)
			{
				props->pos2 += 10;
			}
			if (props->wireRnd == 3)
			{
				props->pos3 += 10;
			}
			if (props->wireRnd == 4)
			{
				props->pos4 += 10;
			}
		}
		if (H3_Button(h3, props->WirePlugText, 720, 576, A_Center + A_Middle))
		{
			H3_Object_SetTranslation(props->PlugUsed3, 2895, 130);
			H3_Object_AddComponent(props->PlugUsed3, SPRITECOMPONENT_CREATE("assets/wires/wire_plug_used.png", A_Middle + A_Center));
			if (props->wireRnd == 1)
			{
				props->pos1 += 100;
			}
			if (props->wireRnd == 2)
			{
				props->pos2 += 100;
			}
			if (props->wireRnd == 3)
			{
				props->pos3 += 100;
			}
			if (props->wireRnd == 4)
			{
				props->pos4 += 100;
			}
		}
		if (H3_Button(h3, props->WirePlugText, 720, 734, A_Center + A_Middle))
		{
			H3_Object_SetTranslation(props->PlugUsed4, 2895, 210);
			H3_Object_AddComponent(props->PlugUsed4, SPRITECOMPONENT_CREATE("assets/wires/wire_plug_used.png", A_Middle + A_Center));
			if (props->wireRnd == 1)
			{
				props->pos1 += 1000;
			}
			if (props->wireRnd == 2)
			{
				props->pos2 += 1000;
			}
			if (props->wireRnd == 3)
			{
				props->pos3 += 1000;
			}
			if (props->wireRnd == 4)
			{
				props->pos4 += 1000;
			}
		}
		if (H3_Button(h3, props->WirePlugText, 1120, 255, A_Center + A_Middle))
		{
			H3_Object_SetTranslation(props->PlugUsed5, 3095, -31);
			H3_Object_AddComponent(props->PlugUsed5, SPRITECOMPONENT_CREATE("assets/wires/wire_plug_used.png", A_Middle + A_Center));
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
				props->pos3 += 100;
			}
			if (props->wireRnd == 4)
			{
				props->pos4 += 10;
			}
		}
		if (H3_Button(h3, props->WirePlugText, 1120, 416, A_Center + A_Middle))
		{
			H3_Object_SetTranslation(props->PlugUsed6, 3095, 50);
			H3_Object_AddComponent(props->PlugUsed6, SPRITECOMPONENT_CREATE("assets/wires/wire_plug_used.png", A_Middle + A_Center));
			if (props->wireRnd == 1)
			{
				props->pos1 += 100;
			}
			if (props->wireRnd == 2)
			{
				props->pos2 += 1000;
			}
			if (props->wireRnd == 3)
			{
				props->pos3 += 10;
			}
			if (props->wireRnd == 4)
			{
				props->pos4 += 1;
			}
		}
		if (H3_Button(h3, props->WirePlugText, 1120, 576, A_Center + A_Middle))
		{
			H3_Object_SetTranslation(props->PlugUsed7, 3095, 130);
			H3_Object_AddComponent(props->PlugUsed7, SPRITECOMPONENT_CREATE("assets/wires/wire_plug_used.png", A_Middle + A_Center));
			if (props->wireRnd == 1)
			{
				props->pos1 += 10;
			}
			if (props->wireRnd == 2)
			{
				props->pos2 += 10;
			}
			if (props->wireRnd == 3)
			{
				props->pos3 += 1000;
			}
			if (props->wireRnd == 4)
			{
				props->pos4 += 100;
			}
		}
		if (H3_Button(h3, props->WirePlugText, 1120, 734, A_Center + A_Middle))
		{
			H3_Object_SetTranslation(props->PlugUsed8, 3095, 210);
			H3_Object_AddComponent(props->PlugUsed8, SPRITECOMPONENT_CREATE("assets/wires/wire_plug_used.png", A_Middle + A_Center));
			if (props->wireRnd == 1)
			{
				props->pos1 += 1000;
			}
			if (props->wireRnd == 2)
			{
				props->pos2 += 100;
			}
			if (props->wireRnd == 3)
			{
				props->pos3 += 1;
			}
			if (props->wireRnd == 4)
			{
				props->pos4 += 1000;
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

	properties->WireResolved = false;
	properties->wireOn = false;
	properties->wireCreate = true;
	properties->WirePlug = false;
	properties->place1 = false;
	properties->place2 = false;
	properties->place3 = false;
	properties->place4 = false;
	properties->alreadyplaced1 = false;
	properties->alreadyplaced2 = false;
	properties->alreadyplaced3 = false;
	properties->alreadyplaced4 = false;

	properties->Wire1 = H3_Object_Create2(properties->scene, "Wire1", NULL, 14);
	properties->Wire2 = H3_Object_Create2(properties->scene, "Wire2", NULL, 14);
	properties->Wire3 = H3_Object_Create2(properties->scene, "Wire3", NULL, 14);
	properties->Wire4 = H3_Object_Create2(properties->scene, "Wire4", NULL, 14);
	properties->PlugUsed1 = H3_Object_Create2(properties->scene, "PlugUsed1", NULL, 13);
	properties->PlugUsed2 = H3_Object_Create2(properties->scene, "PlugUsed2", NULL, 13);
	properties->PlugUsed3 = H3_Object_Create2(properties->scene, "PlugUsed3", NULL, 13);
	properties->PlugUsed4 = H3_Object_Create2(properties->scene, "PlugUsed4", NULL, 13);
	properties->PlugUsed5 = H3_Object_Create2(properties->scene, "PlugUsed5", NULL, 13);
	properties->PlugUsed6 = H3_Object_Create2(properties->scene, "PlugUsed6", NULL, 13);
	properties->PlugUsed7 = H3_Object_Create2(properties->scene, "PlugUsed7", NULL, 13);
	properties->PlugUsed8 = H3_Object_Create2(properties->scene, "PlugUsed8", NULL, 13);

	int wiw, wih;
	properties->WirePlugText = H3_Texture_Load("assets/wires/wire_plug.png", &wiw, &wih);

	return properties;
}