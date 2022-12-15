#ifndef _H3_COMPONENTS_DETECTORCOMPONENT_H_
#define _H3_COMPONENTS_DETECTORCOMPONENT_H_

#include <h3.h>

#define DETECTORCOMPONENT_TYPEID 0x04000001

H3_CAPI_BEGIN_BLOCK
void DetectorComponent_Terminate(void* properties);
void DetectorComponent_Update(H3Handle h3, H3Handle object, SH3Transform* transform, float t, float dt, void* properties);
void DetectorComponent_OnCollisionEnter(H3Handle object, SH3Collision Collision);
void* DetectorComponent_CreateProperties(H3Handle Enemie);

//H3_DECLARE_COMPONENT_PROPERTY_ACCESSORS_RO_EX(DetectorComponent, bool, Detect);


H3_CAPI_END_BLOCK

#define DETECTORCOMPONENT_CREATE(ENEMIE)														 \
	(SH3Component) {														             \
		.Terminate          = DetectorComponent_Terminate,                                 \
		.Update             = DetectorComponent_Update,									 \
		.OnCollisionEnter   = DetectorComponent_OnCollisionEnter,							 \
		.isInitialized      = false,                                                     \
		.componentType      = DETECTORCOMPONENT_TYPEID,                                    \
		.properties         = DetectorComponent_CreateProperties(ENEMIE)						 \
	}

#endif /* _H3_COMPONENTS_DETECTORCOMPONENT_H_ */
