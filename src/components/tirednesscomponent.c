#include <components/tirednesscomponent.h>
#include <components/playercomponent.h>

#include <stdlib.h>

typedef struct
{
	H3Handle player;
	int tiredness;

	const char* Text;
	SH3TextProperties Props;
} TirednessComponent_Properties;

void TirednessComponent_Terminate(void* properties)
{
	free(properties);
}

void TirednessComponent_Draw(H3Handle h3, SH3Transform* transform, void* properties)
{
	TirednessComponent_Properties* props = (TirednessComponent_Properties*)properties;
	H3_Font_Printf(h3, props->Props, transform, props->Text, props->tiredness);

	props->tiredness = PlayerComponent_GetTirednessEx(props->player);
}


void* TirednessComponent_CreateProperties(const char* text, SH3TextProperties props, H3Handle player)
{
	TirednessComponent_Properties* properties = malloc(sizeof(TirednessComponent_Properties));

	properties->player = player;
	properties->tiredness = PlayerComponent_GetTirednessEx(properties->player);

	properties->Text = text;
	properties->Props = props;
	return properties;
}

#define CURRENT_COMPONENT_TYPEID TIREDNESSCOMPONENT_TYPEID
H3_DEFINE_COMPONENT_PROPERTY_ACCESSORS_RW(TirednessComponent, const char*, Text);
H3_DEFINE_COMPONENT_PROPERTY_ACCESSORS_RO(TirednessComponent, SH3TextProperties, Props);

H3_DEFINE_COMPONENT_PROPERTY_ACCESSORS_RW_EX(TirednessComponent, TIREDNESSCOMPONENT_TYPEID, const char*, Text);
H3_DEFINE_COMPONENT_PROPERTY_ACCESSORS_RO_EX(TirednessComponent, TIREDNESSCOMPONENT_TYPEID, SH3TextProperties, Props);