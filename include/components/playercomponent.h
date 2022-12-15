#ifndef _H3_COMPONENTS_PLAYERCOMPONENT_H_
#define _H3_COMPONENTS_PLAYERCOMPONENT_H_

#include <h3.h>

typedef enum
{
	OBJ_case_1, //poche n°1
	OBJ_case_2, //poche n°2
	OBJ_case_3, //poche n°3
} EinventoryObjects;

#define PLAYERCOMPONENT_TYPEID 0x10000001

H3_CAPI_BEGIN_BLOCK
void PlayerComponent_Terminate(void* properties);
void PlayerComponent_Update(H3Handle h3, H3Handle object, SH3Transform* transform, float t, float dt, void* properties);
void PlayerComponent_OnCollisionEnter(H3Handle object, SH3Collision collider);
void PlayerComponent_OnTriggerEnter(H3Handle object, SH3Collision collider);
void PlayerComponent_OnTriggerLeave(H3Handle object, H3Handle collider);

void* PlayerComponent_CreateProperties(H3Handle scene, int character);

H3_DECLARE_COMPONENT_PROPERTY_ACCESSORS_RW_EX(PlayerComponent, int, character);
H3_DECLARE_COMPONENT_PROPERTY_ACCESSORS_RW_EX(PlayerComponent, int, Tiredness);

H3_DECLARE_COMPONENT_PROPERTY_ACCESSORS_RW_EX(PlayerComponent, bool, isCatch);
H3_CAPI_END_BLOCK

#define PLAYERCOMPONENT_CREATE(SCENE, CHARACTER)                                \
	(SH3Component) {                                                 \
		.Terminate          = PlayerComponent_Terminate,             \
		.Update             = PlayerComponent_Update,                \
		.OnCollisionEnter   = PlayerComponent_OnCollisionEnter,      \
		.OnTriggerEnter     = PlayerComponent_OnTriggerEnter,        \
		.OnTriggerLeave     = PlayerComponent_OnTriggerLeave,        \
		.isInitialized      = false,                                 \
		.componentType      = PLAYERCOMPONENT_TYPEID,                \
		.properties         = PlayerComponent_CreateProperties(SCENE, CHARACTER)\
	}

#endif /* _H3_COMPONENTS_PLAYERCOMPONENT_H_ */
