#include "EnigmeShape.h"
#include "components/spritecomponent.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct
{
	float cx;
	float cy;
	float ox;
	float oy;
	float tx;
	float ty;
	float rx;
	float ry;
	bool EnigmeUncomplet;
	bool Debut;
	H3Handle scene;
} EnigmeShapeComponent_Properties;

void EnigmeShapeComponent_Terminate(void* properties)
{
	free(properties);
}

void EnigmeShapeComponent_Update(H3Handle h3, H3Handle object, SH3Transform* transform, float t, float dt, void* properties)
{
	EnigmeShapeComponent_Properties* props = (EnigmeShapeComponent_Properties*)properties;

	if (props->EnigmeUncomplet == false)
	{
		if (props->Debut == true)
		{
			H3Handle Circle = H3_Object_Create2(props->scene, "Circle", NULL, 4);
			H3_Object_AddComponent(Circle, SPRITECOMPONENT_CREATE("assets/shapes/circle.png", A_Center + A_Middle));
			H3_Object_SetTranslation(Circle, props->cx, props->cy);

			H3Handle Rectangle = H3_Object_Create2(props->scene, "Rectangle", NULL, 4);
			H3_Object_AddComponent(Rectangle, SPRITECOMPONENT_CREATE("assets/shapes/rectangle.png", A_Center + A_Middle));
			H3_Object_SetTranslation(Rectangle, props->rx, props->ry);

			H3Handle Octogone = H3_Object_Create2(props->scene, "Octogone", NULL, 4);
			H3_Object_AddComponent(Octogone, SPRITECOMPONENT_CREATE("assets/shapes/octogone.png", A_Center + A_Middle));
			H3_Object_SetTranslation(Octogone, props->ox, props->oy);

			H3Handle Triangle = H3_Object_Create2(props->scene, "Triangle", NULL, 4);
			H3_Object_AddComponent(Triangle, SPRITECOMPONENT_CREATE("assets/shapes/triangle.png", A_Center + A_Middle));
			H3_Object_SetTranslation(Triangle, props->tx, props->ty);

			props->Debut = false;
		}

	}
	


}

void* EnigmeShapeComponent_CreateProperties(H3Handle scene)
{
	EnigmeShapeComponent_Properties* properties = malloc(sizeof(EnigmeShapeComponent_Properties));
	H3_ASSERT_CONSOLE(properties, "Failed to allocate properties");

	properties->scene = scene;
	properties->cx = 672;
	properties->cy = 1495;
	properties->ox = 1719;
	properties->oy = 1410;
	properties->tx = 2553;
	properties->ty = 925;
	properties->rx = 2911;
	properties->ry = 771;
	properties->EnigmeUncomplet = false;
	properties->Debut = true;

	return properties;
}