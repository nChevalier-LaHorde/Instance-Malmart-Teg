#ifndef _H3_COMPONENTS_CLOCKCOMPONENT_H_
#define _H3_COMPONENTS_CLOCKCOMPONENT_H_

#include <h3.h>

#define CLOCKCOMPONENT_TYPEID 0x70000001

H3_CAPI_BEGIN_BLOCK
void ClockComponent_Terminate(void* properties);
void ClockComponent_Draw(H3Handle h3, SH3Transform* transform, void* properties);

void* ClockComponent_CreateProperties(const char* text, SH3TextProperties props);

H3_DECLARE_COMPONENT_PROPERTY_ACCESSORS_RW(ClockComponent, const char*, Text);
H3_DECLARE_COMPONENT_PROPERTY_ACCESSORS_RO(ClockComponent, SH3TextProperties, Props);

H3_DECLARE_COMPONENT_PROPERTY_ACCESSORS_RW_EX(ClockComponent, const char*, Text);
H3_DECLARE_COMPONENT_PROPERTY_ACCESSORS_RO_EX(ClockComponent, SH3TextProperties, Props);
H3_DECLARE_COMPONENT_PROPERTY_ACCESSORS_RO_EX(ClockComponent, bool, ingame);
H3_CAPI_END_BLOCK

#define CLOCKCOMPONENT_CREATE(TEXT, PROPS)                                 \
	(SH3Component) {                                                       \
		.Terminate          = ClockComponent_Terminate,                    \
		.Draw               = ClockComponent_Draw,                         \
		.isInitialized      = false,                                       \
		.componentType      = CLOCKCOMPONENT_TYPEID,                       \
		.properties         = ClockComponent_CreateProperties(TEXT, PROPS) \
	}

#endif /* _H3_COMPONENTS_CLOCKCOMPONENT_H_ */
