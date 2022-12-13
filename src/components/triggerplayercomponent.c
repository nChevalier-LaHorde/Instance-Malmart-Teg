#include <components/triggerplayercomponent.h>

#include <stdlib.h>

typedef struct
{
	bool isActive;
	/*float Width;
	float Height;*/
} TriggerPlayerComponent_Properties;

void TriggerPlayerComponent_Terminate(void* properties)
{
	free(properties);
}

void TriggerPlayerComponent_Update(H3Handle h3, H3Handle object, SH3Transform* transform, float t, float dt, void* properties)
{
	TriggerPlayerComponent_Properties* props = (TriggerPlayerComponent_Properties*)properties;

	if (props->isActive == true)
	{
		;
	}
}

void* TriggerPlayerComponent_CreateProperties()
{
	TriggerPlayerComponent_Properties* properties = malloc(sizeof(TriggerPlayerComponent_Properties));
	H3_ASSERT_CONSOLE(properties, "Failed to allocate properties");

	properties->isActive = false;

	return properties;
}

//H3_DEFINE_COMPONENT_PROPERTY_ACCESSORS_RW(TriggerPlayerComponent, bool, isActive);
H3_DEFINE_COMPONENT_PROPERTY_ACCESSORS_RW_EX(TriggerPlayerComponent, TRIGGERPLAYERCOMPONENT_TYPEID, bool, isActive);
