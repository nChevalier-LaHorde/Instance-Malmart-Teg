#include "Detector.h"
#include <components/playercomponent.h>
#include "Enemie.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct
{
	float vx;
	float vy;
	float px;
	float py;
	int mx;
	int my;
	float dist;
	float bx;
	float by;
	//bool Detect;
	H3Handle Enemie;

	bool lock;
} DetectorComponent_Properties;

void DetectorComponent_Terminate(void* properties)
{
	free(properties);
}

void DetectorComponent_OnCollisionEnter(H3Handle object, SH3Collision Collision)
{
	SH3Component* component = H3_Object_GetComponent(object, DETECTORCOMPONENT_TYPEID);
	DetectorComponent_Properties* props = (DetectorComponent_Properties*)(component->properties);

	if (Collision.other == NULL)
	{
		H3_Object_Destroy(object, false);
		EnemieComponent_SetDetectEx(props->Enemie, false);
		//props->Detect = false;
	}
	else if (H3_Object_HasComponent(Collision.other, PLAYERCOMPONENT_TYPEID))
	{
		H3_Object_Destroy(object, false);
		EnemieComponent_SetDetectEx(props->Enemie, true);
		//props->Detect = true;
	}
}

void DetectorComponent_Update(H3Handle h3, H3Handle object, SH3Transform* transform, float t, float dt, void* properties)
{
	DetectorComponent_Properties* props = (DetectorComponent_Properties*)properties;

}





void* DetectorComponent_CreateProperties(H3Handle Enemie)
{
	DetectorComponent_Properties* properties = malloc(sizeof(DetectorComponent_Properties));
	H3_ASSERT_CONSOLE(properties, "Failed to allocate properties");

	//properties->Detect = false;
	properties->Enemie = Enemie;
	/*properties->Width = width;
	properties->Height = height;*/

	return properties;
}

//H3_DEFINE_COMPONENT_PROPERTY_ACCESSORS_RO_EX(DetectorComponent,DETECTORCOMPONENT_TYPEID, bool, Detect);
