#ifndef _H3_COMPONENTS_OBJECTSCOMPONENT_H_
#define _H3_COMPONENTS_OBJECTSCOMPONENT_H_

#include <h3.h>

typedef enum
{
	OBJ_airsoft_gun,
	OBJ_drink,
	OBJ_post_it,
	OBJ_coin,
	OBJ_puzzle,
	OBJ_key,

	OBJ_Void,
} EObjects;

#define OBJECTSCOMPONENT_TYPEID 0x40000001

H3_CAPI_BEGIN_BLOCK
void ObjectsComponent_Terminate(void* properties);
void* ObjectsComponent_CreateProperties(EObjects object);

H3_DECLARE_COMPONENT_PROPERTY_ACCESSORS_RO_EX(ObjectsComponent, EObjects, object);
H3_CAPI_END_BLOCK

#define OBJECTSCOMPONENT_CREATE(OBJECT)                                 \
	(SH3Component) {                                                           \
		.Terminate          = ObjectsComponent_Terminate,               \
		.isInitialized      = false,                                           \
		.componentType      = OBJECTSCOMPONENT_TYPEID,                  \
		.properties         = ObjectsComponent_CreateProperties(OBJECT) \
	}

#endif /* _H3_COMPONENTS_GROUNDEDOBJECTCOMPONENT_H_ */
