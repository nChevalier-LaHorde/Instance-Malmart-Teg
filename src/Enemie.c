#include "Enemie.h"
#include "Detector.h"
#include "components/spritecomponent.h"
#include <components/bulletscomponent.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
//#include <cstdlib>

#include <h3/ui.h>

typedef struct
{
	int pv;
	int init_pv;
	float timer_knocking_out;

	float vex;
	float vey;
	float Timer;
	float TimerDetector;
	float TimerEnemie;
	float rndx;
	float rndy;
	char detector[256];
	int detectorindex;
	H3Handle Player;
	H3Handle scene;
	bool Detect;
	float dpx;
	float dpy;
	bool chasing;
	float aDeg2;
} EnemieComponent_Properties;

void EnemieComponent_Terminate(void* properties)
{
	free(properties);
}

void EnemieComponent_Update(H3Handle h3, H3Handle object, SH3Transform* transform, float t, float dt, void* properties)
{
	EnemieComponent_Properties* props = (EnemieComponent_Properties*)properties;
	float Deltx;
	float Delty;
	float aRad;
	float aDeg;
	float aDeg1;
	float ex;
	float ey;
	float px;
	float py;
	float dist;
	float aDegRnd;
	float bx;
	float by;
	float mx;
	float my;
	float pbx;
	float pby;



	H3_Transform_GetPosition(H3_Object_GetTransform(object), &ex, &ey);
	H3_Transform_GetPosition(H3_Object_GetTransform(props->Player), &px, &py);
	Deltx = px - ex;
	Delty = py - ey;
	aRad = atan2(Delty, Deltx);
	aDeg = aRad * (180 / H3_PI);


	H3_Object_SetRotation(object, 0);

	H3_Input_GetMousePos(h3, &mx, &my);
	float x, y, w, h, vpx, vpy;
	H3_GetView(h3, &x, &y, &w, &h, &vpx, &vpy);

	float x0 = x - w / 2;
	float x1 = x + w / 2;
	float y0 = y - h / 2;
	float y1 = y + h / 2;

	float mx01 = mx / vpx;
	float my01 = my / vpy;

	float mxScene = x0 + (x1 - x0) * mx01;
	float myScene = y0 + (y1 - y0) * my01;

	float dx = mxScene - px;
	float dy = myScene - py;


	dist = sqrtf((px - ex) * (px - ex) + (py - ey) * (py - ey));


	if (props->pv > 0)
	{
		//RAYCAST
		if (H3_GetTime() - props->TimerDetector > 0.5 && dist <= 300)
		{
			props->detectorindex += 1;
			snprintf(props->detector, 256, "detector_%d", props->detectorindex);
			H3Handle Detector = H3_Object_Create(props->scene, props->detector, NULL);

			H3_Object_EnablePhysics(Detector, H3_BOX_COLLIDER(CDT_Dynamic, 4, 6, 0x22, true));
			H3_Object_AddComponent(Detector, DETECTORCOMPONENT_CREATE(object));
			bx = ((px - ex) / dist) * 2000;
			by = ((py - ey) / dist) * 2000;
			pbx = ((px - ex) / dist) * 50;
			pby = ((py - ey) / dist) * 50;
			H3_Object_SetVelocity(Detector, bx, by);
			H3_Object_SetRotation(Detector, aDeg + 90);
			H3_Object_SetTranslation(Detector, ex + pbx, ey + pby);
			props->TimerDetector = H3_GetTime();
		}


		//POURSUITE
		if (dist <= 300 && props->Detect == true)
		{
			props->vex = ((px - ex) / (dist + 1)) * 96;
			props->vey = ((py - ey) / (dist + 1)) * 96;


			props->dpx = px;
			props->dpy = py;

			props->chasing = true;

			props->aDeg2 = (atan2((props->dpx - ex), (props->dpy - ey)) * (180 / H3_PI)) + 180;
			props->TimerEnemie = H3_GetTime();

		}
		if (props->chasing == true)
		{
			if (props->dpy < ey)
			{

				props->vex = ((props->dpx - ex) / (dist + 1)) * 64;
				props->vey = ((props->dpy - ey) / (dist + 1)) * 64;
				props->dpy -= 1;

				if (H3_Ui_BeginWindow(H3_Object_GetName(object)))
				{
					H3_Ui_Printf("haut");
				}
				H3_Ui_EndWindow();

			}
			if (props->dpy > ey)
			{
				props->vex = ((props->dpx - ex) / (dist + 1)) * 64;
				props->vey = ((props->dpy - ey) / (dist + 1)) * 64;
				props->dpy += 1;

				if (H3_Ui_BeginWindow(H3_Object_GetName(object)))
				{
					H3_Ui_Printf("bas");
				}
				H3_Ui_EndWindow();
			}
			if (props->dpx > ex)
			{
				props->vex = ((props->dpx - ex) / (dist + 1)) * 64;
				props->vey = ((props->dpy - ey) / (dist + 1)) * 64;
				props->dpx += 1;

				if (H3_Ui_BeginWindow(H3_Object_GetName(object)))
				{
					H3_Ui_Printf("droite");
				}
				H3_Ui_EndWindow();
			}
			if (props->dpx < ex)
			{

				props->vex = ((props->dpx - ex) / (dist + 1)) * 64;
				props->vey = ((props->dpy - ey) / (dist + 1)) * 64;
				props->dpx -= 1;

				if (H3_Ui_BeginWindow(H3_Object_GetName(object)))
				{
					H3_Ui_Printf("gauche");
				}
				H3_Ui_EndWindow();
			}



			if (dist >= 300 && H3_GetTime() - props->TimerEnemie > 3)
			{
				props->chasing = false;
				props->TimerEnemie = H3_GetTime();
			}

		}
		if (props->chasing == false)
		{
			props->vex = ((props->rndx - ex) / (dist + 1)) * 64;
			props->vey = ((props->rndy - ey) / (dist + 1)) * 64;
			//printf("Unchasing");
			if (H3_GetTime() - props->Timer > 5)
			{
				props->Timer = H3_GetTime();
				props->rndx = rand() % 500;
				props->rndy = rand() % 500;
			}
		}

		H3_Object_SetVelocity(object, props->vex, props->vey);

		/*if (H3_GetTime() - props->Timer > 2)
		{
			printf("dpx = %f\n", props->dpx);
			printf("dpy = %f\n", props->dpy);
			printf("ex = %f\n", ex);
			printf("ey = %f\n", ey);
			props->Timer = H3_GetTime();
		}*/
		if (H3_Ui_BeginWindow(H3_Object_GetName(object)))
		{
			H3_Ui_Printf("Angle to player: %f", props->aDeg2);
		}
		H3_Ui_EndWindow();
	}

	//knocking out
	else if (props->pv == 0)
	{
		H3_Object_RemoveComponent(object, SPRITECOMPONENT_TYPEID);
		if (props->init_pv == 20) H3_Object_AddComponent(object, SPRITECOMPONENT_CREATE("assets/PlayerAndEnemiesSprites/miniboss_knockedout.png", A_Center + A_Middle));
		else if (props->init_pv == 5) H3_Object_AddComponent(object, SPRITECOMPONENT_CREATE("assets/PlayerAndEnemiesSprites/enemie_knockedout.png", A_Center + A_Middle));

		if (H3_GetTime() - props->timer_knocking_out >= 30)
		{
			props->pv = props->init_pv;
			H3_Object_RemoveComponent(object, SPRITECOMPONENT_TYPEID);
			if (props->init_pv == 20) H3_Object_AddComponent(object, SPRITECOMPONENT_CREATE("assets/PlayerAndEnemiesSprites/miniboss.png", A_Center + A_Middle));
			else if (props->init_pv == 5) H3_Object_AddComponent(object, SPRITECOMPONENT_CREATE("assets/PlayerAndEnemiesSprites/enemie.png", A_Center + A_Middle));
		}
	}
}

void EnemieComponent_OnCollisionEnter(H3Handle object, SH3Collision collider)
{
	SH3Component* component = H3_Object_GetComponent(object, ENEMIECOMPONENT_TYPEID);
	EnemieComponent_Properties* props = (EnemieComponent_Properties*)component->properties;

	if (collider.other != NULL && H3_Object_HasComponent(collider.other, BULLETSCOMPONENT_TYPEID))
	{
		if (props->pv > 0)
		{
			props->pv -= 1;
			props->timer_knocking_out = H3_GetTime();
		}
	}
}

void* EnemieComponent_CreateProperties(H3Handle Player, H3Handle scene, int pv)
{
	EnemieComponent_Properties* properties = malloc(sizeof(EnemieComponent_Properties));
	H3_ASSERT_CONSOLE(properties, "Failed to allocate properties");

	properties->pv = pv;
	properties->init_pv = pv;

	properties->chasing = false;
	properties->Detect = false;
	properties->scene = scene;
	properties->rndx = 0;
	properties->rndy = 0;
	properties->Player = Player;
	properties->Timer = H3_GetTime();
	properties->TimerEnemie = H3_GetTime();
	/*properties->Deltx = 0.0f;
	properties->Delty = 0.0f;
	properties->aRad = 0.0f;
	properties->aDeg = 0.0f;
	properties->px = 0.0f;
	properties->py = 0.0f;
	properties->vx = 0.0f;
	properties->vy = 0.0f;*/

	return properties;
}
H3_DEFINE_COMPONENT_PROPERTY_ACCESSORS_RW_EX(EnemieComponent, ENEMIECOMPONENT_TYPEID, bool, Detect);