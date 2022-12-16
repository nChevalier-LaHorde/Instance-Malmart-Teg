#include "Equation.h"
#include "components/spritecomponent.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include <h3/ui.h>

typedef struct
{
	int GameOver;
	float px;
	float py;
	int Resol;
	bool used1;
	bool used2;
	bool used3;
	bool used4;
	bool used5;
	bool used6;
	bool used7;
	bool used8;
	bool used9;
	bool nbr1;
	bool nbr2;
	bool nbr3;
	bool nbr4;
	bool nbr5;
	bool nbr6;
	bool nbr7;
	bool nbr8;
	bool nbr9;
	bool place1;
	bool place2;
	bool place3;
	bool place4;
	bool place5;
	bool EquationOn;
	bool EquationCreate;
	bool EquationResolved;
	H3Handle chiffre1;
	H3Handle chiffre2;
	H3Handle chiffre3;
	H3Handle chiffre4;
	H3Handle chiffre5;
	H3Handle chiffre6;
	H3Handle chiffre7;
	H3Handle chiffre8;
	H3Handle chiffre9;
	H3Handle T1;
	H3Handle T2;
	H3Handle T3;
	H3Handle T4;
	H3Handle T5;
	H3Handle T6;
	H3Handle T7;
	H3Handle T8;
	H3Handle T9;
	H3Handle Equation;
	H3Handle Equation1Tex;
	H3Handle Equation2Tex;
	H3Handle Equation3Tex;
	H3Handle Equation4Tex;
	H3Handle Equation5Tex;
	H3Handle Equation6Tex;
	H3Handle Equation7Tex;
	H3Handle Equation8Tex;
	H3Handle Equation9Tex;
	H3Handle Player;
	H3Handle scene;

} EquationComponent_Properties;

void EquationComponent_Terminate(void* properties)
{
	free(properties);
}

void EquationComponent_Update(H3Handle h3, H3Handle object, SH3Transform* transform, float t, float dt, void* properties)
{
	EquationComponent_Properties* props = (EquationComponent_Properties*)properties;

	H3_Transform_GetPosition(H3_Object_GetTransform(props->Player), &props->px, &props->py);



	if (props->EquationCreate == true)
	{
		props->Equation = H3_Object_Create2(props->scene, "Equation", NULL, 11);
		H3_Object_SetTranslation(props->Equation, 3730, 285);
		props->EquationCreate = false;
	}

	/*if (H3_Ui_BeginWindow("Equation"))
	{
		H3_Ui_Printf("Resol = %d", props->Resol);
	}
	H3_Ui_EndWindow();*/

	if (props->EquationResolved == false)
	{
		if (H3_Input_IsKeyPressed(K_Space))
		{
			
			if (3720 < props->px && props->px < 3735 && 290>props->py && props->py > 284)
			{
				H3_Object_AddComponent(props->Equation, SPRITECOMPONENT_CREATE("assets/equation/pannel.png", A_Center + A_Middle));
				props->EquationOn = true;
				
			}
		}
		else if (props->py > 286)
		{
			props->EquationOn = false;
			H3_Object_Destroy(props->Equation, false);
			props->EquationCreate = true;
			H3_Object_RemoveComponent(props->chiffre1, SPRITECOMPONENT_TYPEID);
			H3_Object_RemoveComponent(props->chiffre2, SPRITECOMPONENT_TYPEID);
			H3_Object_RemoveComponent(props->chiffre3, SPRITECOMPONENT_TYPEID);
			H3_Object_RemoveComponent(props->chiffre4, SPRITECOMPONENT_TYPEID);
			H3_Object_RemoveComponent(props->chiffre5, SPRITECOMPONENT_TYPEID);
			H3_Object_RemoveComponent(props->chiffre6, SPRITECOMPONENT_TYPEID);
			H3_Object_RemoveComponent(props->chiffre7, SPRITECOMPONENT_TYPEID);
			H3_Object_RemoveComponent(props->chiffre8, SPRITECOMPONENT_TYPEID);
			H3_Object_RemoveComponent(props->chiffre9, SPRITECOMPONENT_TYPEID);
			H3_Object_RemoveComponent(props->T1, SPRITECOMPONENT_TYPEID);
			H3_Object_RemoveComponent(props->T2, SPRITECOMPONENT_TYPEID);
			H3_Object_RemoveComponent(props->T3, SPRITECOMPONENT_TYPEID);
			H3_Object_RemoveComponent(props->T4, SPRITECOMPONENT_TYPEID);
			H3_Object_RemoveComponent(props->T5, SPRITECOMPONENT_TYPEID);
			H3_Object_RemoveComponent(props->T6, SPRITECOMPONENT_TYPEID);
			H3_Object_RemoveComponent(props->T7, SPRITECOMPONENT_TYPEID);
			H3_Object_RemoveComponent(props->T8, SPRITECOMPONENT_TYPEID);
			H3_Object_RemoveComponent(props->T9, SPRITECOMPONENT_TYPEID);
			props->Resol = 0;
		}



		
		if (props->EquationOn == true)
		{
			H3_Object_SetTranslation(props->Player, 3730, 285);

			if (props->place1 == false && props->place2 == false && props->place3 == false && props->place4 == false && props->place5 == false)
			{
				if(props->nbr1 == true)
				{
					H3_Object_SetTranslation(props->chiffre1, 3625, 150);
					H3_Object_AddComponent(props->chiffre1, SPRITECOMPONENT_CREATE("assets/equation/1.png", A_Middle + A_Center));
					props->place1 = true;
					props->used1 = true;
					props->Resol += 1;
				}

				if (props->nbr2 == true)
				{
					H3_Object_SetTranslation(props->chiffre2, 3625, 150);
					H3_Object_AddComponent(props->chiffre2, SPRITECOMPONENT_CREATE("assets/equation/2.png", A_Middle + A_Center));
					props->place1 = true;
					props->used2 = true;
					props->Resol += 1;
				}
				if(props->nbr3 == true)
				{
					H3_Object_SetTranslation(props->chiffre3, 3625, 150);
					H3_Object_AddComponent(props->chiffre3, SPRITECOMPONENT_CREATE("assets/equation/3.png", A_Middle + A_Center));
					props->place1 = true;
					props->used3 = true;
					props->Resol += 1;
				}
				if (props->nbr4 == true)
				{
					H3_Object_SetTranslation(props->chiffre4, 3625, 150);
					H3_Object_AddComponent(props->chiffre4, SPRITECOMPONENT_CREATE("assets/equation/4.png", A_Middle + A_Center));
					props->place1 = true;
					props->used4 = true;
					props->Resol += 1;
				}
				if (props->nbr5 == true)
				{
					H3_Object_SetTranslation(props->chiffre5, 3625, 150);
					H3_Object_AddComponent(props->chiffre5, SPRITECOMPONENT_CREATE("assets/equation/5.png", A_Middle + A_Center));
					props->place1 = true;
					props->used5 = true;
					props->Resol += 2;
				}
				if (props->nbr6 == true)
				{
					H3_Object_SetTranslation(props->chiffre6, 3625, 150);
					H3_Object_AddComponent(props->chiffre6, SPRITECOMPONENT_CREATE("assets/equation/6.png", A_Middle + A_Center));
					props->place1 = true;
					props->used6 = true;
					props->Resol += 1;
				}
				if (props->nbr7 == true)
				{
					H3_Object_SetTranslation(props->chiffre7, 3625, 150);
					H3_Object_AddComponent(props->chiffre7, SPRITECOMPONENT_CREATE("assets/equation/7.png", A_Middle + A_Center));
					props->place1 = true;
					props->used7 = true;
					props->Resol += 1;
				}
				if (props->nbr8 == true)
				{
					H3_Object_SetTranslation(props->chiffre8, 3625, 150);
					H3_Object_AddComponent(props->chiffre8, SPRITECOMPONENT_CREATE("assets/equation/8.png", A_Middle + A_Center));
					props->place1 = true;
					props->used8 = true;
					props->Resol += 1;
				}
				if (props->nbr9 == true)
				{
					H3_Object_SetTranslation(props->chiffre9, 3625, 150);
					H3_Object_AddComponent(props->chiffre9, SPRITECOMPONENT_CREATE("assets/equation/9.png", A_Middle + A_Center));
					props->place1 = true;
					props->used9 = true;
					props->Resol += 1;
				}
			}
			
			if (props->place1 == true && props->place2 == false && props->place3 == false && props->place4 == false && props->place5 == false)
			{
				if (props->nbr1 == true)
				{
					if (props->used1 == false)
					{
						H3_Object_SetTranslation(props->chiffre1, 3675, 150);
						H3_Object_AddComponent(props->chiffre1, SPRITECOMPONENT_CREATE("assets/equation/1.png", A_Middle + A_Center));
						props->place2 = true;
						props->used1 = true;
						props->Resol += 1;
					}					
				}
				if (props->nbr2 == true)
				{
					if (props->used2 == false)
					{
						H3_Object_SetTranslation(props->chiffre2, 3675, 150);
						H3_Object_AddComponent(props->chiffre2, SPRITECOMPONENT_CREATE("assets/equation/2.png", A_Middle + A_Center));
						props->place2 = true;
						props->used2 = true;
						props->Resol += 1;
					}
				}
				if (props->nbr3 == true)
				{
					if (props->used3 == false)
					{
						H3_Object_SetTranslation(props->chiffre3, 3675, 150);
						H3_Object_AddComponent(props->chiffre3, SPRITECOMPONENT_CREATE("assets/equation/3.png", A_Middle + A_Center));
						props->place2 = true;
						props->used3 = true;
						props->Resol += 1;
					}
				}
				if(props->nbr4 == true)
				{
					if (props->used4 == false)
					{
						H3_Object_SetTranslation(props->chiffre4, 3675, 150);
						H3_Object_AddComponent(props->chiffre4, SPRITECOMPONENT_CREATE("assets/equation/4.png", A_Middle + A_Center));
						props->place2 = true;
						props->used4 = true;
						props->Resol += 1;
					}
				}
				if (props->nbr5 == true)
				{
					if (props->used5 == false)
					{
						H3_Object_SetTranslation(props->chiffre5, 3675, 150);
						H3_Object_AddComponent(props->chiffre5, SPRITECOMPONENT_CREATE("assets/equation/5.png", A_Middle + A_Center));
						props->place2 = true;
						props->used5 = true;
						props->Resol += 1;
					}
				}
				if (props->nbr6 == true)
				{
					if (props->used6 == false)
					{
						H3_Object_SetTranslation(props->chiffre6, 3675, 150);
						H3_Object_AddComponent(props->chiffre6, SPRITECOMPONENT_CREATE("assets/equation/6.png", A_Middle + A_Center));
						props->place2 = true;
						props->used6 = true;
						props->Resol += 2;
					}
				}
				if (props->nbr7 == true)
				{
					if (props->used7 == false)
					{
						H3_Object_SetTranslation(props->chiffre7, 3675, 150);
						H3_Object_AddComponent(props->chiffre7, SPRITECOMPONENT_CREATE("assets/equation/7.png", A_Middle + A_Center));
						props->place2 = true;
						props->used7 = true;
						props->Resol += 1;
					}
				}
				if (props->nbr8 == true)
				{
					if (props->used8 == false)
					{
						H3_Object_SetTranslation(props->chiffre8, 3675, 150);
						H3_Object_AddComponent(props->chiffre8, SPRITECOMPONENT_CREATE("assets/equation/8.png", A_Middle + A_Center));
						props->place2 = true;
						props->used8 = true;
						props->Resol += 1;
					}
				}
				if (props->nbr9 == true)
				{
					if (props->used9 == false)
					{
						H3_Object_SetTranslation(props->chiffre9, 3675, 150);
						H3_Object_AddComponent(props->chiffre9, SPRITECOMPONENT_CREATE("assets/equation/9.png", A_Middle + A_Center));
						props->place2 = true;
						props->used9 = true;
						props->Resol += 1;
					}
				}
			}
			if (props->place1 == true && props->place2 == true && props->place3 == false && props->place4 == false && props->place5 == false)
			{
				if (props->nbr1 == true)
				{
					if (props->used1 == false)
					{
						H3_Object_SetTranslation(props->chiffre1, 3725, 150);
						H3_Object_AddComponent(props->chiffre1, SPRITECOMPONENT_CREATE("assets/equation/1.png", A_Middle + A_Center));
						props->place3= true;
						props->used1 = true;
						props->Resol += 1;
					}
				}
				if (props->nbr2 == true)
				{
					if (props->used2 == false)
					{
						H3_Object_SetTranslation(props->chiffre2, 3725, 150);
						H3_Object_AddComponent(props->chiffre2, SPRITECOMPONENT_CREATE("assets/equation/2.png", A_Middle + A_Center));
						props->place3 = true;
						props->used2 = true;
						props->Resol += 2;
					}
				}
				if (props->nbr3 == true)
				{
					if (props->used3 == false)
					{
						H3_Object_SetTranslation(props->chiffre3, 3725, 150);
						H3_Object_AddComponent(props->chiffre3, SPRITECOMPONENT_CREATE("assets/equation/3.png", A_Middle + A_Center));
						props->place3 = true;
						props->used3 = true;
						props->Resol += 1;
					}
				}
				if (props->nbr4 == true)
				{
					if (props->used4 == false)
					{
						H3_Object_SetTranslation(props->chiffre4, 3725, 150);
						H3_Object_AddComponent(props->chiffre4, SPRITECOMPONENT_CREATE("assets/equation/4.png", A_Middle + A_Center));
						props->place3 = true;
						props->used4 = true;
						props->Resol += 1;
					}
				}
				if (props->nbr5 == true)
				{
					if (props->used5 == false)
					{
						H3_Object_SetTranslation(props->chiffre5, 3725, 150);
						H3_Object_AddComponent(props->chiffre5, SPRITECOMPONENT_CREATE("assets/equation/5.png", A_Middle + A_Center));
						props->place3 = true;
						props->used5 = true;
						props->Resol += 1;
					}
				}
				if (props->nbr6 == true)
				{
					if (props->used6 == false)
					{
						H3_Object_SetTranslation(props->chiffre6, 3725, 150);
						H3_Object_AddComponent(props->chiffre6, SPRITECOMPONENT_CREATE("assets/equation/6.png", A_Middle + A_Center));
						props->place3 = true;
						props->used6 = true;
						props->Resol += 1;
					}
				}
				if (props->nbr7 == true)
				{
					if (props->used7 == false)
					{
						H3_Object_SetTranslation(props->chiffre7, 3725, 150);
						H3_Object_AddComponent(props->chiffre7, SPRITECOMPONENT_CREATE("assets/equation/7.png", A_Middle + A_Center));
						props->place3 = true;
						props->used7 = true;
						props->Resol += 1;
					}
				}
				if (props->nbr8 == true)
				{
					if (props->used8 == false)
					{
						H3_Object_SetTranslation(props->chiffre8, 3725, 150);
						H3_Object_AddComponent(props->chiffre8, SPRITECOMPONENT_CREATE("assets/equation/8.png", A_Middle + A_Center));
						props->place3 = true;
						props->used8 = true;
						props->Resol += 1;
					}
				}
				if (props->nbr9 == true)
				{
					if (props->used9 == false)
					{
						H3_Object_SetTranslation(props->chiffre9, 3725, 150);
						H3_Object_AddComponent(props->chiffre9, SPRITECOMPONENT_CREATE("assets/equation/9.png", A_Middle + A_Center));
						props->place3 = true;
						props->used9 = true;
						props->Resol += 1;
					}
				}
			}
			if (props->place1 == true && props->place2 == true && props->place3 == true && props->place4 == false && props->place5 == false)
			{
				if (props->nbr1 == true)
				{
					if (props->used1 == false)
					{
						H3_Object_SetTranslation(props->chiffre1, 3775, 150);
						H3_Object_AddComponent(props->chiffre1, SPRITECOMPONENT_CREATE("assets/equation/1.png", A_Middle + A_Center));
						props->place4 = true;
						props->used1 = true;
						props->Resol += 1;
					}
				}
				if (props->nbr2 == true)
				{
					if (props->used2 == false)
					{
						H3_Object_SetTranslation(props->chiffre2, 3775, 150);
						H3_Object_AddComponent(props->chiffre2, SPRITECOMPONENT_CREATE("assets/equation/2.png", A_Middle + A_Center));
						props->place4 = true;
						props->used2 = true;
						props->Resol += 1;
					}
				}
				if (props->nbr3 == true)
				{
					if (props->used3 == false)
					{
						H3_Object_SetTranslation(props->chiffre3, 3775, 150);
						H3_Object_AddComponent(props->chiffre3, SPRITECOMPONENT_CREATE("assets/equation/3.png", A_Middle + A_Center));
						props->place4 = true;
						props->used3 = true;
						props->Resol += 1;
					}
				}
				if (props->nbr4 == true)
				{
					if (props->used4 == false)
					{
						H3_Object_SetTranslation(props->chiffre4, 3775, 150);
						H3_Object_AddComponent(props->chiffre4, SPRITECOMPONENT_CREATE("assets/equation/4.png", A_Middle + A_Center));
						props->place4 = true;
						props->used4 = true;
						props->Resol += 1;
					}
				}
				if (props->nbr5 == true)
				{
					if (props->used5 == false)
					{
						H3_Object_SetTranslation(props->chiffre5, 3775, 150);
						H3_Object_AddComponent(props->chiffre5, SPRITECOMPONENT_CREATE("assets/equation/5.png", A_Middle + A_Center));
						props->place4 = true;
						props->used5 = true;
						props->Resol += 1;
					}
				}
				if (props->nbr6 == true)
				{
					if (props->used6 == false)
					{
						H3_Object_SetTranslation(props->chiffre6, 3775, 150);
						H3_Object_AddComponent(props->chiffre6, SPRITECOMPONENT_CREATE("assets/equation/6.png", A_Middle + A_Center));
						props->place4 = true;
						props->used6 = true;
						props->Resol += 1;
					}
				}
				if (props->nbr7 == true)
				{
					if (props->used7 == false)
					{
						H3_Object_SetTranslation(props->chiffre7, 3775, 150);
						H3_Object_AddComponent(props->chiffre7, SPRITECOMPONENT_CREATE("assets/equation/7.png", A_Middle + A_Center));
						props->place4 = true;
						props->used7 = true;
						props->Resol += 1;
					}
				}
				if (props->nbr8 == true)
				{
					if (props->used8 == false)
					{
						H3_Object_SetTranslation(props->chiffre8, 3775, 150);
						H3_Object_AddComponent(props->chiffre8, SPRITECOMPONENT_CREATE("assets/equation/8.png", A_Middle + A_Center));
						props->place4 = true;
						props->used8 = true;
						props->Resol += 1;
					}
				}
				if (props->nbr9 == true)
				{
					if (props->used9 == false)
					{
						H3_Object_SetTranslation(props->chiffre9, 3775, 150);
						H3_Object_AddComponent(props->chiffre9, SPRITECOMPONENT_CREATE("assets/equation/9.png", A_Middle + A_Center));
						props->place4 = true;
						props->used9 = true;
						props->Resol += 2;
					}
				}
			}
			if (props->place1 == true && props->place2 == true && props->place3 == true && props->place4 == true && props->place5 == false)
			{
				if (props->nbr1 == true)
				{
					if (props->used1 == false)
					{
						H3_Object_SetTranslation(props->chiffre1, 3825, 150);
						H3_Object_AddComponent(props->chiffre1, SPRITECOMPONENT_CREATE("assets/equation/1.png", A_Middle + A_Center));
						props->place5 = true;
						props->used1 = true;
						props->Resol += 1;
					}
				}
				if (props->nbr2 == true)
				{
					if (props->used2 == false)
					{
						H3_Object_SetTranslation(props->chiffre2, 3825, 150);
						H3_Object_AddComponent(props->chiffre2, SPRITECOMPONENT_CREATE("assets/equation/2.png", A_Middle + A_Center));
						props->place5 = true;
						props->used2 = true;
						props->Resol += 1;
					}
				}
				if (props->nbr3 == true)
				{
					if (props->used3 == false)
					{
						H3_Object_SetTranslation(props->chiffre3, 3825, 150);
						H3_Object_AddComponent(props->chiffre3, SPRITECOMPONENT_CREATE("assets/equation/3.png", A_Middle + A_Center));
						props->place5 = true;
						props->used3 = true;
						props->Resol += 1;
					}
				}
				if (props->nbr4 == true)
				{
					if (props->used4 == false)
					{
						H3_Object_SetTranslation(props->chiffre4, 3825, 150);
						H3_Object_AddComponent(props->chiffre4, SPRITECOMPONENT_CREATE("assets/equation/4.png", A_Middle + A_Center));
						props->place5 = true;
						props->used4 = true;
						props->Resol += 1;
					}
				}
				if (props->nbr5 == true)
				{
					if (props->used5 == false)
					{
						H3_Object_SetTranslation(props->chiffre5, 3825, 150);
						H3_Object_AddComponent(props->chiffre5, SPRITECOMPONENT_CREATE("assets/equation/5.png", A_Middle + A_Center));
						props->place5 = true;
						props->used5 = true;
						props->Resol += 1;
					}
				}
				if (props->nbr6 == true)
				{
					if (props->used6 == false)
					{
						H3_Object_SetTranslation(props->chiffre6, 3825, 150);
						H3_Object_AddComponent(props->chiffre6, SPRITECOMPONENT_CREATE("assets/equation/6.png", A_Middle + A_Center));
						props->place5 = true;
						props->used6 = true;
						props->Resol += 1;
					}
				}
				if (props->nbr7 == true)
				{
					if (props->used7 == false)
					{
						H3_Object_SetTranslation(props->chiffre7, 3825, 150);
						H3_Object_AddComponent(props->chiffre7, SPRITECOMPONENT_CREATE("assets/equation/7.png", A_Middle + A_Center));
						props->place5 = true;
						props->used7 = true;
						props->Resol += 2;
					}
				}
				if (props->nbr8 == true)
				{
					if (props->used8 == false)
					{
						H3_Object_SetTranslation(props->chiffre8, 3825, 150);
						H3_Object_AddComponent(props->chiffre8, SPRITECOMPONENT_CREATE("assets/equation/8.png", A_Middle + A_Center));
						props->place5 = true;
						props->used8 = true;
						props->Resol += 1;
					}
				}
				if (props->nbr9 == true)
				{
					if (props->used9 == false)
					{
						H3_Object_SetTranslation(props->chiffre9, 3825, 150);
						H3_Object_AddComponent(props->chiffre9, SPRITECOMPONENT_CREATE("assets/equation/9.png", A_Middle + A_Center));
						props->place5 = true;
						props->used9 = true;
						props->Resol += 1;
					}
				}
			}
			if (props->place1 == true && props->place2 == true && props->place3 == true && props->place4 == true && props->place5 == true)
			{
				if (props->Resol == 10)
				{
					props->EquationResolved = true;
					props->EquationOn = false;
					H3_Object_Destroy(props->Equation, false);
					props->EquationCreate = false;
					H3_Object_RemoveComponent(props->chiffre1, SPRITECOMPONENT_TYPEID);
					H3_Object_RemoveComponent(props->chiffre2, SPRITECOMPONENT_TYPEID);
					H3_Object_RemoveComponent(props->chiffre3, SPRITECOMPONENT_TYPEID);
					H3_Object_RemoveComponent(props->chiffre4, SPRITECOMPONENT_TYPEID);
					H3_Object_RemoveComponent(props->chiffre5, SPRITECOMPONENT_TYPEID);
					H3_Object_RemoveComponent(props->chiffre6, SPRITECOMPONENT_TYPEID);
					H3_Object_RemoveComponent(props->chiffre7, SPRITECOMPONENT_TYPEID);
					H3_Object_RemoveComponent(props->chiffre8, SPRITECOMPONENT_TYPEID);
					H3_Object_RemoveComponent(props->chiffre9, SPRITECOMPONENT_TYPEID);
					H3_Object_RemoveComponent(props->T1, SPRITECOMPONENT_TYPEID);
					H3_Object_RemoveComponent(props->T2, SPRITECOMPONENT_TYPEID);
					H3_Object_RemoveComponent(props->T3, SPRITECOMPONENT_TYPEID);
					H3_Object_RemoveComponent(props->T4, SPRITECOMPONENT_TYPEID);
					H3_Object_RemoveComponent(props->T5, SPRITECOMPONENT_TYPEID);
					H3_Object_RemoveComponent(props->T6, SPRITECOMPONENT_TYPEID);
					H3_Object_RemoveComponent(props->T7, SPRITECOMPONENT_TYPEID);
					H3_Object_RemoveComponent(props->T8, SPRITECOMPONENT_TYPEID);
					H3_Object_RemoveComponent(props->T9, SPRITECOMPONENT_TYPEID);
				}
				else
				{
					H3_Object_SetTranslation(props->Player, 3730,290);
					props->nbr1 = false;
					props->nbr2 = false;
					props->nbr3 = false;
					props->nbr4 = false;
					props->nbr5 = false;
					props->nbr6 = false;
					props->nbr7 = false;
					props->nbr8 = false;
					props->nbr9 = false;
					props->place1 = false;
					props->place2 = false;
					props->place3 = false;
					props->place4 = false;
					props->place5 = false;
				}
			}
		}

		if (props->GameOver == 3)
		{
			//ACCESSOR isCatch
			/*if (H3_Ui_BeginWindow("Coffee"))
			{
				H3_Ui_Printf("GameOver = true");
			}
			H3_Ui_EndWindow();*/
		}

	}
}

void EquationComponent_Draw(H3Handle h3, SH3Transform* transform, void* properties)
{
	EquationComponent_Properties* props = (EquationComponent_Properties*)properties;

	if (props->EquationOn == true)
	{
		if (H3_Button(h3, props->Equation1Tex, 735, 496, A_Center + A_Middle))
		{
			props->nbr1 = true;
			H3_Object_SetTranslation(props->T1, 3641, 280);
			H3_Object_AddComponent(props->T1, SPRITECOMPONENT_CREATE("assets/equation/pannelbuttondisapear.png", A_Middle + A_Center));
		}
		if (H3_Button(h3, props->Equation2Tex, 915, 496, A_Center + A_Middle))
		{
			props->nbr2 = true;
			H3_Object_SetTranslation(props->T2, 3731, 280);
			H3_Object_AddComponent(props->T2, SPRITECOMPONENT_CREATE("assets/equation/pannelbuttondisapear.png", A_Middle + A_Center));
		}
		if (H3_Button(h3, props->Equation3Tex, 1095, 496, A_Center + A_Middle))
		{
			props->nbr3 = true;
			H3_Object_SetTranslation(props->T3, 3820, 280);
			H3_Object_AddComponent(props->T3, SPRITECOMPONENT_CREATE("assets/equation/pannelbuttondisapear.png", A_Middle + A_Center));
		}
		if (H3_Button(h3, props->Equation4Tex, 735, 628, A_Center + A_Middle))
		{
			props->nbr4 = true;
			H3_Object_SetTranslation(props->T4, 3641, 346);
			H3_Object_AddComponent(props->T4, SPRITECOMPONENT_CREATE("assets/equation/pannelbuttondisapear.png", A_Middle + A_Center));
		}
		if (H3_Button(h3, props->Equation5Tex, 915, 628, A_Center + A_Middle))
		{
			props->nbr5 = true;
			H3_Object_SetTranslation(props->T5, 3731, 346);
			H3_Object_AddComponent(props->T5, SPRITECOMPONENT_CREATE("assets/equation/pannelbuttondisapear.png", A_Middle + A_Center));
		}
		if (H3_Button(h3, props->Equation6Tex, 1095, 628, A_Center + A_Middle))
		{
			props->nbr6 = true;
			H3_Object_SetTranslation(props->T6, 3820, 346);
			H3_Object_AddComponent(props->T6, SPRITECOMPONENT_CREATE("assets/equation/pannelbuttondisapear.png", A_Middle + A_Center));
		}
		if (H3_Button(h3, props->Equation7Tex, 735, 760, A_Center + A_Middle))
		{
			props->nbr7 = true;
			H3_Object_SetTranslation(props->T7, 3641, 412);
			H3_Object_AddComponent(props->T7, SPRITECOMPONENT_CREATE("assets/equation/pannelbuttondisapear.png", A_Middle + A_Center));
		}
		if (H3_Button(h3, props->Equation8Tex, 915, 760, A_Center + A_Middle))
		{
			props->nbr8 = true;
			H3_Object_SetTranslation(props->T8, 3731, 412);
			H3_Object_AddComponent(props->T8, SPRITECOMPONENT_CREATE("assets/equation/pannelbuttondisapear.png", A_Middle + A_Center));
		}
		if (H3_Button(h3, props->Equation9Tex, 1090, 760, A_Center + A_Middle))
		{
			props->nbr9 = true;
			H3_Object_SetTranslation(props->T9, 3820, 412);
			H3_Object_AddComponent(props->T9, SPRITECOMPONENT_CREATE("assets/equation/pannelbuttondisapear.png", A_Middle + A_Center));
		}
	}
}

void* EquationComponent_CreateProperties(H3Handle scene, H3Handle Player)
{
	EquationComponent_Properties* properties = malloc(sizeof(EquationComponent_Properties));
	H3_ASSERT_CONSOLE(properties, "Failed to allocate properties");

	properties->Player = Player;
	properties->scene = scene;
	properties->chiffre1 = H3_Object_Create2(properties->scene, "Chiffre1", NULL, 13);
	properties->chiffre2 = H3_Object_Create2(properties->scene, "Chiffre2", NULL, 13);
	properties->chiffre3 = H3_Object_Create2(properties->scene, "Chiffre3", NULL, 13);
	properties->chiffre4 = H3_Object_Create2(properties->scene, "Chiffre4", NULL, 13);
	properties->chiffre5 = H3_Object_Create2(properties->scene, "Chiffre5", NULL, 13);
	properties->chiffre6 = H3_Object_Create2(properties->scene, "Chiffre6", NULL, 13);
	properties->chiffre7 = H3_Object_Create2(properties->scene, "Chiffre7", NULL, 13);
	properties->chiffre8 = H3_Object_Create2(properties->scene, "Chiffre8", NULL, 13);
	properties->chiffre9 = H3_Object_Create2(properties->scene, "Chiffre9", NULL, 13);
	properties->T1 = H3_Object_Create2(properties->scene, "T1", NULL, 14);
	properties->T2 = H3_Object_Create2(properties->scene, "T2", NULL, 14);
	properties->T3 = H3_Object_Create2(properties->scene, "T3", NULL, 14);
	properties->T4 = H3_Object_Create2(properties->scene, "T4", NULL, 14);
	properties->T5 = H3_Object_Create2(properties->scene, "T5", NULL, 14);
	properties->T6 = H3_Object_Create2(properties->scene, "T6", NULL, 14);
	properties->T7 = H3_Object_Create2(properties->scene, "T7", NULL, 14);
	properties->T8 = H3_Object_Create2(properties->scene, "T8", NULL, 14);
	properties->T9 = H3_Object_Create2(properties->scene, "T9", NULL, 14);

	properties->Resol = 0;

	properties->used1 = false;
	properties->used2 = false;
	properties->used3 = false;
	properties->used4 = false;
	properties->used5 = false;
	properties->used6 = false;
	properties->used7 = false;
	properties->used8 = false;
	properties->used9 = false;
	properties->nbr1 = false;
	properties->nbr2 = false;
	properties->nbr3 = false;
	properties->nbr4 = false;
	properties->nbr5 = false;
	properties->nbr6 = false;
	properties->nbr7 = false;
	properties->nbr8 = false;
	properties->nbr9 = false;
	properties->place1 = false;
	properties->place2 = false;
	properties->place3 = false;
	properties->place4 = false;
	properties->place5 = false;
	properties->EquationOn = false;
	properties->EquationResolved = false;
	properties->EquationCreate = true;

	int e1w, e1h;
	properties->Equation1Tex = H3_Texture_Load("assets/equation/pannelbutton.png", &e1w, &e1h);
	int e2w, e2h;
	properties->Equation2Tex = H3_Texture_Load("assets/equation/pannelbutton.png", &e2w, &e2h);
	int e3w, e3h;
	properties->Equation3Tex = H3_Texture_Load("assets/equation/pannelbutton.png", &e3w, &e3h);
	int e4w, e4h;
	properties->Equation4Tex = H3_Texture_Load("assets/equation/pannelbutton.png", &e4w, &e4h);
	int e5w, e5h;
	properties->Equation5Tex = H3_Texture_Load("assets/equation/pannelbutton.png", &e5w, &e5h);
	int e6w, e6h;
	properties->Equation6Tex = H3_Texture_Load("assets/equation/pannelbutton.png", &e6w, &e6h);
	int e7w, e7h;
	properties->Equation7Tex = H3_Texture_Load("assets/equation/pannelbutton.png", &e7w, &e7h);
	int e8w, e8h;
	properties->Equation8Tex = H3_Texture_Load("assets/equation/pannelbutton.png", &e8w, &e8h);
	int e9w, e9h;
	properties->Equation9Tex = H3_Texture_Load("assets/equation/pannelbutton.png", &e9w, &e9h);

	return properties;
}