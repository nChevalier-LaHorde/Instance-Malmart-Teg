#ifndef _H3_COMPONENTS_WIRECOMPONENT_H_
#define _H3_COMPONENTS_WIRECOMPONENT_H_

#include <h3.h>

#define WIRECOMPONENT_TYPEID 0x10000007

H3_CAPI_BEGIN_BLOCK
void WireComponent_Terminate(void* properties);
void WireComponent_Update(H3Handle h3, H3Handle object, SH3Transform* transform, float t, float dt, void* properties);
void WireComponent_Draw(H3Handle h3, SH3Transform* transform, void* properties);
void* WireComponent_CreateProperties(H3Handle scene, H3Handle Player);

H3_CAPI_END_BLOCK

#define WIRECOMPONENT_CREATE(SCENE,PLAYER)                                 \
	(SH3Component) {                                                 \
		.Terminate          = WireComponent_Terminate,             \
		.Update             = WireComponent_Update,                \
		.Draw               = WireComponent_Draw, \
		.isInitialized      = false,                                 \
		.componentType      = WIRECOMPONENT_TYPEID,                \
		.properties         = WireComponent_CreateProperties(SCENE,PLAYER) \
	}

#endif /* _H3_COMPONENTS_WIRECOMPONENT_H_ */
