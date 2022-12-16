#include <components/clockcomponent.h>
#include <components/playercomponent.h>

#include <stdlib.h>

typedef struct
{
	bool ingame;
	
	int hours;
	
	int unit_minutes;
	int dozen_minutes;
	float secondes;

	const char* Text;
	SH3TextProperties Props;
} ClockComponent_Properties;

void ClockComponent_Terminate(void* properties)
{
	free(properties);
}

void ClockComponent_Draw(H3Handle h3, SH3Transform* transform, void* properties)
{
	ClockComponent_Properties* props = (ClockComponent_Properties*)properties;
	H3_Font_Printf(h3, props->Props, transform, props->Text, props->hours, props->dozen_minutes, props->unit_minutes);
	
	if (props->ingame == true)
	{
		// 1s irl = 1min in game
		if (H3_GetTime() - props->secondes >= 1)
		{
			props->secondes = H3_GetTime();
			props->unit_minutes += 1;

			if (props->unit_minutes == 10)
			{
				props->unit_minutes = 0;
				props->dozen_minutes += 1;

				if (props->dozen_minutes == 6)
				{
					props->dozen_minutes = 0;
					props->hours += 1;

					if (props->hours == 24)
					{
						props->hours = 0;
					}
				}
			}

			if (props->hours == 8 && props->dozen_minutes == 3 && props->unit_minutes == 0)
			{
				;
			}
		}
	}

}


void* ClockComponent_CreateProperties(const char* text, SH3TextProperties props)
{
	ClockComponent_Properties* properties = malloc(sizeof(ClockComponent_Properties));
	properties->Text = text;
	properties->Props = props;

	properties->ingame = true;

	properties->hours = 21;
	properties->dozen_minutes = 3;
	properties->unit_minutes = 0;
	properties->secondes = H3_GetTime();


	return properties;
}

#define CURRENT_COMPONENT_TYPEID CLOCKCOMPONENT_TYPEID
H3_DEFINE_COMPONENT_PROPERTY_ACCESSORS_RW(ClockComponent, const char*, Text);
H3_DEFINE_COMPONENT_PROPERTY_ACCESSORS_RO(ClockComponent, SH3TextProperties, Props);

H3_DEFINE_COMPONENT_PROPERTY_ACCESSORS_RW_EX(ClockComponent, CLOCKCOMPONENT_TYPEID, const char*, Text);
H3_DEFINE_COMPONENT_PROPERTY_ACCESSORS_RO_EX(ClockComponent, CLOCKCOMPONENT_TYPEID, SH3TextProperties, Props);
H3_DEFINE_COMPONENT_PROPERTY_ACCESSORS_RO_EX(ClockComponent, CLOCKCOMPONENT_TYPEID, bool, ingame);