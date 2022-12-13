#include <components/inventorycomponent.h>
#include <stdlib.h>

typedef struct
{
	EObjects case_1;
	EObjects case_2;
	EObjects case_3;

} InventoryComponent_Properties;

void InventoryComponent_Terminate(void* properties)
{
	free(properties);
}

void InventoryComponent_Update(H3Handle h3, H3Handle object, SH3Transform* transform, float t, float dt, void* properties)
{
	InventoryComponent_Properties* props = (InventoryComponent_Properties*)properties;
}

void* InventoryComponent_CreateProperties()
{
	InventoryComponent_Properties* properties = malloc(sizeof(InventoryComponent_Properties));
	H3_ASSERT_CONSOLE(properties, "Failed to allocate properties");

	properties->case_1 = OBJ_Void;
	properties->case_2 = OBJ_Void;
	properties->case_3 = OBJ_Void;

	return properties;
}

H3_DEFINE_COMPONENT_PROPERTY_ACCESSORS_RW_EX(InventoryComponent, INVENTORYCOMPONENT_TYPEID, EObjects, case_1);
H3_DEFINE_COMPONENT_PROPERTY_ACCESSORS_RW_EX(InventoryComponent, INVENTORYCOMPONENT_TYPEID, EObjects, case_2);
H3_DEFINE_COMPONENT_PROPERTY_ACCESSORS_RW_EX(InventoryComponent, INVENTORYCOMPONENT_TYPEID, EObjects, case_3);
