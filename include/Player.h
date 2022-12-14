#ifndef _H3_COMPONENTS_PLAYERCOMPONENT_H_
#define _H3_COMPONENTS_PLAYERCOMPONENT_H_

#include <h3.h>

#define PLAYERCOMPONENT_TYPEID 0x10000003

H3_CAPI_BEGIN_BLOCK
void PlayerComponent_Terminate(void* properties);
void PlayerComponent_Update(H3Handle h3, H3Handle object, SH3Transform* transform, float t, float dt, void* properties);
void* PlayerComponent_CreateProperties(H3Handle scene);

H3_CAPI_END_BLOCK

#define PLAYERCOMPONENT_CREATE(SCENE)                                 \
	(SH3Component) {                                                 \
		.Terminate          = PlayerComponent_Terminate,             \
		.Update             = PlayerComponent_Update,                \
		.isInitialized      = false,                                 \
		.componentType      = PLAYERCOMPONENT_TYPEID,                \
		.properties         = PlayerComponent_CreateProperties(SCENE) \
	}

#endif /* _H3_COMPONENTS_PLAYERCOMPONENT_H_ */
