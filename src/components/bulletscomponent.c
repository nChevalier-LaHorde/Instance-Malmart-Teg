#include <components/bulletscomponent.h>
#include <Enemie.h>

#include <stdlib.h>

typedef struct
{
	int Useless;
} BulletsComponent_Properties;

void BulletsComponent_Terminate(void* properties)
{
	free(properties);
}

void BulletsComponent_Update(H3Handle h3, H3Handle object, SH3Transform* transform, float t, float dt, void* properties)
{
	BulletsComponent_Properties* props = (BulletsComponent_Properties*)properties;

}

void* BulletsComponent_CreateProperties()
{
	BulletsComponent_Properties* properties = malloc(sizeof(BulletsComponent_Properties));
	H3_ASSERT_CONSOLE(properties, "Failed to allocate properties");

	properties->Useless = 0;

	return properties;
}

void BulletsComponent_OnCollisionEnter(H3Handle object, SH3Collision collider)
{
	if (collider.other == NULL || H3_Object_HasComponent(collider.other, ENEMIECOMPONENT_TYPEID))
	{
		H3_Object_Destroy(object, false);
	}
}
