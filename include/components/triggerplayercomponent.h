#ifndef _H3_COMPONENTS_TRIGGERPLAYERCOMPONENT_H_
#define _H3_COMPONENTS_TRIGGERPLAYERCOMPONENT_H_

#include <h3.h>

#define TRIGGERPLAYERCOMPONENT_TYPEID 0x20000001

H3_CAPI_BEGIN_BLOCK
void TriggerPlayerComponent_Terminate(void* properties);
void TriggerPlayerComponent_Update(H3Handle h3, H3Handle object, SH3Transform* transform, float t, float dt, void* properties);

void* TriggerPlayerComponent_CreateProperties();

//H3_DECLARE_COMPONENT_PROPERTY_ACCESSORS_RW(TriggerPlayerComponent, bool, isActive);
H3_DECLARE_COMPONENT_PROPERTY_ACCESSORS_RW_EX(TriggerPlayerComponent, bool, isActive);
H3_CAPI_END_BLOCK

#define TRIGGERPLAYERCOMPONENT_CREATE()                                 \
	(SH3Component) {                                                    \
		.Terminate          = TriggerPlayerComponent_Terminate,         \
		.Update             = TriggerPlayerComponent_Update,            \
		.isInitialized      = false,                                    \
		.componentType      = TRIGGERPLAYERCOMPONENT_TYPEID,            \
		.properties         = TriggerPlayerComponent_CreateProperties() \
	}

#endif /* _H3_COMPONENTS_TRIGGERPLAYERCOMPONENT_H_ */
