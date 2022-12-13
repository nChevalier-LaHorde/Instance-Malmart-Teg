#ifndef _H3_COMPONENTS_INVENTORYCOMPONENT_H_
#define _H3_COMPONENTS_INVENTORYCOMPONENT_H_

#include <h3.h>
#include <components/objectscomponent.h>

#define INVENTORYCOMPONENT_TYPEID 0x50000001

H3_CAPI_BEGIN_BLOCK
void InventoryComponent_Terminate(void* properties);
void InventoryComponent_Update(H3Handle h3, H3Handle object, SH3Transform* transform, float t, float dt, void* properties);

void* InventoryComponent_CreateProperties();

H3_DECLARE_COMPONENT_PROPERTY_ACCESSORS_RW_EX(InventoryComponent, EObjects, case_1);
H3_DECLARE_COMPONENT_PROPERTY_ACCESSORS_RW_EX(InventoryComponent, EObjects, case_2);
H3_DECLARE_COMPONENT_PROPERTY_ACCESSORS_RW_EX(InventoryComponent, EObjects, case_3);
H3_CAPI_END_BLOCK

#define INVENTORYCOMPONENT_CREATE()                                \
	(SH3Component) {                                               \
		.Terminate          = InventoryComponent_Terminate,        \
		.Update             = InventoryComponent_Update,           \
		.isInitialized      = false,                               \
		.componentType      = INVENTORYCOMPONENT_TYPEID,           \
		.properties         = InventoryComponent_CreateProperties()\
	}

#endif /* _H3_COMPONENTS_INVENTORYCOMPONENT_H_ */
