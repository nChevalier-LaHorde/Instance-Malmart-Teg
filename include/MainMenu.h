#ifndef _H3_COMPONENTS_MAINMENUCOMPONENT_H_
#define _H3_COMPONENTS_MAINMENUCOMPONENT_H_

#include <h3.h>

#define MAINMENUCOMPONENT_TYPEID 0x10000006

H3_CAPI_BEGIN_BLOCK
void MainMenuComponent_Terminate(void* properties);
void MainMenuComponent_Update(H3Handle h3, H3Handle object, SH3Transform* transform, float t, float dt, void* properties);
void MainMenuComponent_Draw(H3Handle h3, SH3Transform* transform, void* properties);
void* MainMenuComponent_CreateProperties(H3Handle Player);

H3_DECLARE_COMPONENT_PROPERTY_ACCESSORS_RO_EX(MainMenuComponent, bool, Ending);
H3_DECLARE_COMPONENT_PROPERTY_ACCESSORS_RO_EX(MainMenuComponent, bool, lunching);

H3_CAPI_END_BLOCK

#define MAINMENUCOMPONENT_CREATE(PLAYER)                                 \
	(SH3Component) {                                                 \
		.Terminate          = MainMenuComponent_Terminate,             \
		.Update             = MainMenuComponent_Update,                \
		.Draw               = MainMenuComponent_Draw, \
		.isInitialized      = false,                                 \
		.componentType      = MAINMENUCOMPONENT_TYPEID,                \
		.properties         = MainMenuComponent_CreateProperties(PLAYER) \
	}

#endif /* _H3_COMPONENTS_MAINMENUCOMPONENT_H_ */
