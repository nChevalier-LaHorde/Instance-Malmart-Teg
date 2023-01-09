#ifndef _H3_COMPONENTS_TIREDNESSCOMPONENT_H_
#define _H3_COMPONENTS_TIREDNESSCOMPONENT_H_

#include <h3.h>

#define TIREDNESSCOMPONENT_TYPEID 0x80000001

H3_CAPI_BEGIN_BLOCK
void TirednessComponent_Terminate(void* properties);
void TirednessComponent_Draw(H3Handle h3, SH3Transform* transform, void* properties);

void* TirednessComponent_CreateProperties(const char* text, SH3TextProperties props, H3Handle player);

H3_DECLARE_COMPONENT_PROPERTY_ACCESSORS_RW(TirednessComponent, const char*, Text);
H3_DECLARE_COMPONENT_PROPERTY_ACCESSORS_RO(TirednessComponent, SH3TextProperties, Props);

H3_DECLARE_COMPONENT_PROPERTY_ACCESSORS_RW_EX(TirednessComponent, const char*, Text);
H3_DECLARE_COMPONENT_PROPERTY_ACCESSORS_RO_EX(TirednessComponent, SH3TextProperties, Props);
H3_CAPI_END_BLOCK

#define TIREDNESSCOMPONENT_CREATE(TEXT, PROPS, PLAYER)                                 \
	(SH3Component) {                                                      \
		.Terminate          = TirednessComponent_Terminate,                    \
		.Draw               = TirednessComponent_Draw,                         \
		.isInitialized      = false,                                      \
		.componentType      = TIREDNESSCOMPONENT_TYPEID,                     \
		.properties         = TirednessComponent_CreateProperties(TEXT, PROPS, PLAYER) \
	}

#endif /* _H3_COMPONENTS_TEXTCOMPONENT_H_ */
