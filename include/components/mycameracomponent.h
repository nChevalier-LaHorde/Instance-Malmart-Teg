#ifndef _H3_COMPONENTS_MYCAMERACOMPONENT_H_
#define _H3_COMPONENTS_MYCAMERACOMPONENT_H_

#include <h3.h>

#define MYCAMERACOMPONENT_TYPEID 0x60000001

H3_CAPI_BEGIN_BLOCK
void MyCameraComponent_Terminate(void* properties);
void MyCameraComponent_Update(H3Handle h3, H3Handle object, SH3Transform* transform, float t, float dt, void* properties);

void* MyCameraComponent_CreateProperties(float width, float height, H3Handle player);

H3_DECLARE_COMPONENT_PROPERTY_ACCESSORS_RW(MyCameraComponent, float, Width);
H3_DECLARE_COMPONENT_PROPERTY_ACCESSORS_RW(MyCameraComponent, float, Height);
H3_DECLARE_COMPONENT_PROPERTY_ACCESSORS_RW(MyCameraComponent, H3Handle, player);
H3_DECLARE_COMPONENT_PROPERTY_ACCESSORS_RW_EX(MyCameraComponent, float, Width);
H3_DECLARE_COMPONENT_PROPERTY_ACCESSORS_RW_EX(MyCameraComponent, float, Height);
H3_DECLARE_COMPONENT_PROPERTY_ACCESSORS_RW_EX(MyCameraComponent, H3Handle, player);
H3_CAPI_END_BLOCK

#define MYCAMERACOMPONENT_CREATE(W, H, P)                                 \
	(SH3Component) {                                                 \
		.Terminate          = MyCameraComponent_Terminate,             \
		.Update             = MyCameraComponent_Update,                \
		.isInitialized      = false,                                 \
		.componentType      = MYCAMERACOMPONENT_TYPEID,                \
		.properties         = MyCameraComponent_CreateProperties(W, H, P) \
	}

#endif /* _H3_COMPONENTS_MYCAMERACOMPONENT_H_ */
