#ifndef _H3_COMPONENTS_EQUATIONCOMPONENT_H_
#define _H3_COMPONENTS_EQUATIONCOMPONENT_H_

#include <h3.h>

#define EQUATIONCOMPONENT_TYPEID 0x10000005

H3_CAPI_BEGIN_BLOCK
void EquationComponent_Terminate(void* properties);
void EquationComponent_Update(H3Handle h3, H3Handle object, SH3Transform* transform, float t, float dt, void* properties);
void EquationComponent_Draw(H3Handle h3, SH3Transform* transform, void* properties);
void* EquationComponent_CreateProperties(H3Handle scene, H3Handle Player);

H3_CAPI_END_BLOCK

#define EQUATIONCOMPONENT_CREATE(SCENE,PLAYER)                                 \
	(SH3Component) {                                                 \
		.Terminate          = EquationComponent_Terminate,             \
		.Update             = EquationComponent_Update,                \
		.Draw               = EquationComponent_Draw, \
		.isInitialized      = false,                                 \
		.componentType      = EQUATIONCOMPONENT_TYPEID,                \
		.properties         = EquationComponent_CreateProperties(SCENE,PLAYER) \
	}

#endif /* _H3_COMPONENTS_EQUATIONCOMPONENT_H_ */
