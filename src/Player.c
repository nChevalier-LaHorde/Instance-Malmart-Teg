#include "Player.h"
#include "Detector.h"
#include "components/spritecomponent.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct
{
	float vx;
	float vy;
	char bullet[256];
	int bulletindex;
	H3Handle scene;
} PlayerComponent_Properties;

void PlayerComponent_Terminate(void* properties)
{
	free(properties);
}

void PlayerComponent_Update(H3Handle h3, H3Handle object, SH3Transform* transform, float t, float dt, void* properties)
{
	PlayerComponent_Properties* props = (PlayerComponent_Properties*)properties;
	float Deltx;
	float Delty;
	float aRad;
	float aDeg;
	float px;
	float py;
	int mx;
	int my;
	float dist;
	float bx;
	float by;


	H3_Transform_GetPosition(H3_Object_GetTransform(object), &px, &py);
	H3_Input_GetMousePos(h3, &mx, &my);

	if (H3_Ui_BeginWindow(H3_Object_GetName(object)))
	{
		H3_Ui_Printf("Coordinates: (%f, %f)", px, py);
	}
	H3_Ui_EndWindow();

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

	aRad = atan2(dy, dx);
	aDeg = aRad * H3_RAD2DEG;
	H3_Object_SetRotation(object, 0);
	dist = sqrtf((mxScene - px) * (mxScene - px) + (myScene - py) * (myScene - py));

	//CALCULE BULLET
	/*float degrees = atan2((my - py), (mx - px));*/
	float y2 = ((px + 50 - px) * sin(aDeg + 90)) + ((py - py) * cos(aDeg + 90)) + py;
	float x2 = ((px + 50 - px) * cos(aDeg + 90)) - ((py - py) * sin(aDeg + 90)) + px;


	if (H3_Input_IsKeyDown(K_Right))
	{
		props->vx = 128;
	}
	else if (H3_Input_IsKeyDown(K_Left))
	{
		props->vx = -128;
	}
	else
	{
		props->vx = 0;
	}

	if (H3_Input_IsKeyDown(K_Up))
	{
		props->vy = -128;
	}
	else if (H3_Input_IsKeyDown(K_Down))
	{
		props->vy = 128;
	}
	else
	{
		props->vy = 0;
	};

	H3_Object_SetVelocity(object, props->vx, props->vy);




}

void* PlayerComponent_CreateProperties(H3Handle scene)
{
	PlayerComponent_Properties* properties = malloc(sizeof(PlayerComponent_Properties));
	H3_ASSERT_CONSOLE(properties, "Failed to allocate properties");

	properties->scene = scene;
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