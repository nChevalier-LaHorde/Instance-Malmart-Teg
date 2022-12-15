#include "MainMenu.h"
#include "components/spritecomponent.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <h3/ui.h>

typedef struct
{
	bool lunching;
	bool inGame;
	bool DoQuit;
	H3Handle Play;
	H3Handle Quit;
	H3Handle Player;

} MainMenuComponent_Properties;

void MainMenuComponent_Terminate(void* properties)
{
	free(properties);
}

void MainMenuComponent_Update(H3Handle h3, H3Handle object, SH3Transform* transform, float t, float dt, void* properties)
{
	MainMenuComponent_Properties* props = (MainMenuComponent_Properties*)properties;


	if (props->lunching == true)
	{
		if (props->inGame == true)
		{
			H3_Object_Translate(props->Player, 3995, 1095);
			props->lunching = false;
		}
	}
}

void MainMenuComponent_Draw(H3Handle h3, SH3Transform* transform, void* properties)
{
	MainMenuComponent_Properties* props = (MainMenuComponent_Properties*)properties;

	if (H3_Button(h3, props->Play, 390, 672, A_Middle + A_Center))
	{
		props->inGame = true;
	}
	if (H3_Button(h3, props->Quit, 1112, 658, A_Middle + A_Center))
	{
		props->DoQuit = true;
	}
	
}

void* MainMenuComponent_CreateProperties(H3Handle Player)
{
	MainMenuComponent_Properties* properties = malloc(sizeof(MainMenuComponent_Properties));
	H3_ASSERT_CONSOLE(properties, "Failed to allocate properties");

	properties->Player = Player;

	properties->lunching = true;
	properties->inGame = false;
	properties->DoQuit = false;

	int plw, plh;
	properties->Play = H3_Texture_Load("assets/menus/start_start_button.png", &plw, &plh);
	int qlw, qlh;
	properties->Quit = H3_Texture_Load("assets/menus/start_quit_button.png", &qlw, &qlh);

	return properties;
}

H3_DEFINE_COMPONENT_PROPERTY_ACCESSORS_RO_EX(MainMenuComponent, MAINMENUCOMPONENT_TYPEID, bool, inGame);