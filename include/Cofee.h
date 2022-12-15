#ifndef _H3_COMPONENTS_COFEECOMPONENT_H_
#define _H3_COMPONENTS_COFEECOMPONENT_H_

#include <h3.h>

#define COFEECOMPONENT_TYPEID 0x10000001

H3_CAPI_BEGIN_BLOCK
void CofeeComponent_Terminate(void* properties);
void CofeeComponent_Update(H3Handle h3, H3Handle object, SH3Transform* transform, float t, float dt, void* properties);
void CofeeComponent_Draw(H3Handle h3, SH3Transform* transform, void* properties);
void* CofeeComponent_CreateProperties(H3Handle scene, H3Handle Player);

H3_CAPI_END_BLOCK

#define COFEECOMPONENT_CREATE(SCENE,PLAYER)                                 \
	(SH3Component) {                                                 \
		.Terminate          = CofeeComponent_Terminate,             \
		.Update             = CofeeComponent_Update,                \
		.Draw               = CofeeComponent_Draw, \
		.isInitialized      = false,                                 \
		.componentType      = COFEECOMPONENT_TYPEID,                \
		.properties         = CofeeComponent_CreateProperties(SCENE,PLAYER) \
	}

#endif /* _H3_COMPONENTS_COFEECOMPONENT_H_ */
