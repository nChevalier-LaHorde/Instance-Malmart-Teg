#include <components/objectscomponent.h>
#include <components/playercomponent.h>

#include <stdlib.h>

typedef struct
{
	EObjects object;
} ObjectsComponent_Properties;

void ObjectsComponent_Terminate(void* properties)
{
	free(properties);
}

void* ObjectsComponent_CreateProperties(EObjects object)
{
	ObjectsComponent_Properties* properties = malloc(sizeof(ObjectsComponent_Properties));
	H3_ASSERT_CONSOLE(properties, "Failed to allocate properties");

	properties->object = object;

	return properties;
}

H3_DEFINE_COMPONENT_PROPERTY_ACCESSORS_RO_EX(ObjectsComponent, OBJECTSCOMPONENT_TYPEID, EObjects, object);
