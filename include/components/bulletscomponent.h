#ifndef _H3_COMPONENTS_BULLETSCOMPONENT_H_
#define _H3_COMPONENTS_BULLETSCOMPONENT_H_

#include <h3.h>

#define BULLETSCOMPONENT_TYPEID 0x30000001

H3_CAPI_BEGIN_BLOCK
void BulletsComponent_Terminate(void* properties);
void BulletsComponent_Update(H3Handle h3, H3Handle object, SH3Transform* transform, float t, float dt, void* properties);
void BulletsComponent_OnCollisionEnter(H3Handle object, SH3Collision collider);

void* BulletsComponent_CreateProperties();

H3_CAPI_END_BLOCK

#define BULLETSCOMPONENT_CREATE()                                 \
	(SH3Component) {                                              \
		.Terminate          = BulletsComponent_Terminate,         \
		.Update             = BulletsComponent_Update,            \
		.OnCollisionEnter   = BulletsComponent_OnCollisionEnter , \
		.isInitialized      = false,                              \
		.componentType      = BULLETSCOMPONENT_TYPEID,            \
		.properties         = BulletsComponent_CreateProperties() \
	}

#endif /* _H3_COMPONENTS_BULLETSCOMPONENT_H_ */
