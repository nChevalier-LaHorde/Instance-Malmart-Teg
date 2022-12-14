#ifndef _H3_COMPONENTS_ENIGMESHAPECOMPONENT_H_
#define _H3_COMPONENTS_ENIGMESHAPECOMPONENT_H_

#include <h3.h>

#define ENIGMESHAPECOMPONENT_TYPEID 0x10000003

H3_CAPI_BEGIN_BLOCK
void EnigmeShapeComponent_Terminate(void* properties);
void EnigmeShapeComponent_Update(H3Handle h3, H3Handle object, SH3Transform* transform, float t, float dt, void* properties);
void* EnigmeShapeComponent_CreateProperties(H3Handle scene);

H3_CAPI_END_BLOCK

#define ENIGMESHAPECOMPONENT_CREATE(SCENE)                                 \
	(SH3Component) {                                                 \
		.Terminate          = EnigmeShapeComponent_Terminate,             \
		.Update             = EnigmeShapeComponent_Update,                \
		.isInitialized      = false,                                 \
		.componentType      = ENIGMESHAPECOMPONENT_TYPEID,                \
		.properties         = EnigmeShapeComponent_CreateProperties(SCENE) \
	}

#endif /* _H3_COMPONENTS_ENIGMESHAPECOMPONENT_H_ */
