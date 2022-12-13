#include <components/mycameracomponent.h>

#include <stdlib.h>

typedef struct
{
	float Width;
	float Height;
	H3Handle player;
} MyCameraComponent_Properties;

void MyCameraComponent_Terminate(void* properties)
{
	free(properties);
}

void MyCameraComponent_Update(H3Handle h3, H3Handle object, SH3Transform* transform, float t, float dt, void* properties)
{
	MyCameraComponent_Properties* props = (MyCameraComponent_Properties*)properties;
	H3_SetView(h3, transform, props->Width, props->Height);

	float player_x, player_y;
	H3_Transform_GetPosition(H3_Object_GetTransform(props->player), &player_x, &player_y);
	H3_Object_SetTranslation(object, player_x, player_y);

}

void* MyCameraComponent_CreateProperties(float width, float height, H3Handle player)
{
	MyCameraComponent_Properties* properties = malloc(sizeof(MyCameraComponent_Properties));
	H3_ASSERT_CONSOLE(properties, "Failed to allocate properties");

	properties->Width = width;
	properties->Height = height;
	properties->player = player;

	return properties;
}

H3_DEFINE_COMPONENT_PROPERTY_ACCESSORS_RW(MyCameraComponent, float, Width);
H3_DEFINE_COMPONENT_PROPERTY_ACCESSORS_RW(MyCameraComponent, float, Height);
H3_DEFINE_COMPONENT_PROPERTY_ACCESSORS_RW(MyCameraComponent, H3Handle, player);
H3_DEFINE_COMPONENT_PROPERTY_ACCESSORS_RW_EX(MyCameraComponent, MYCAMERACOMPONENT_TYPEID, float, Width);
H3_DEFINE_COMPONENT_PROPERTY_ACCESSORS_RW_EX(MyCameraComponent, MYCAMERACOMPONENT_TYPEID, float, Height);
H3_DEFINE_COMPONENT_PROPERTY_ACCESSORS_RW_EX(MyCameraComponent, MYCAMERACOMPONENT_TYPEID, H3Handle, player);
