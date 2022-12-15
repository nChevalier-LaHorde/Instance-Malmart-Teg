#ifndef _H3_COMPONENTS_ENEMIECOMPONENT_H_
#define _H3_COMPONENTS_ENEMIECOMPONENT_H_

#include <h3.h>

#define ENEMIECOMPONENT_TYPEID 0x10000003

H3_CAPI_BEGIN_BLOCK
void EnemieComponent_Terminate(void* properties);
void EnemieComponent_Update(H3Handle h3, H3Handle object, SH3Transform* transform, float t, float dt, void* properties);
void* EnemieComponent_CreateProperties(H3Handle Player, H3Handle scene);

H3_DECLARE_COMPONENT_PROPERTY_ACCESSORS_RW_EX(EnemieComponent, bool, Detect);

H3_CAPI_END_BLOCK

#define ENEMIECOMPONENT_CREATE(PLAYER,SCENE)                                 \
	(SH3Component) {                                                   \
		.Terminate          = EnemieComponent_Terminate,               \
		.Update             = EnemieComponent_Update,                  \
		.OnCollisionEnter   = EnemieComponent_OnCollisionEnter,	 \
		.isInitialized      = false,                                   \
		.componentType      = ENEMIECOMPONENT_TYPEID,                  \
		.properties         = EnemieComponent_CreateProperties(PLAYER,SCENE) \
	}

#endif /* _H3_COMPONENTS_ENEMIECOMPONENT_H_ */
