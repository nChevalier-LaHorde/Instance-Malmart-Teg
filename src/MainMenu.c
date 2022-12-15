#include "MainMenu.h"
#include "components/spritecomponent.h"
#include <components/playercomponent.h>
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
	bool Ending;
	H3Handle Play;
	H3Handle Quit;
	H3Handle Retry;
	H3Handle Player;

} MainMenuComponent_Properties;

void MainMenuComponent_Terminate(void* properties)
{
	free(properties);
}

void MainMenuComponent_Update(H3Handle h3, H3Handle object, SH3Transform* transform, float t, float dt, void* properties)
{
	MainMenuComponent_Properties* props = (MainMenuComponent_Properties*)properties;


	if (props->lunching == true )
	{
		if (props->inGame == true)
		{
			H3_Object_SetTranslation(props->Player, 27, 849);
			props->lunching = false;
		}
	}
	if (props->Ending == true)
	{
		if (props->inGame == true)
		{
			H3_Object_SetTranslation(props->Player, 27, 849);
			props->Ending = false;
			PlayerComponent_SetisCatchEx(props->Player, false);
		}
	}

	if (PlayerComponent_GetisCatchEx(props->Player) == true)
	{
		props->inGame = false;
		props->Ending = true;
		if (props->Ending == true)
		{
			H3_Object_SetTranslation(props->Player, -1000, -1000);
		}
	}
}

void MainMenuComponent_Draw(H3Handle h3, SH3Transform* transform, void* properties)
{
	MainMenuComponent_Properties* props = (MainMenuComponent_Properties*)properties;
	if (props->lunching == true)
	{
		if (H3_Button(h3, props->Play, 390, 720, A_Middle + A_Center))
		{
			props->inGame = true;
		}
		if (H3_Button(h3, props->Quit, 1130, 720, A_Middle + A_Center))
		{
			props->DoQuit = true;
		}
	}
	if (props->Ending == true)
	{
		if (H3_Button(h3, props->Retry, 240, 670, A_Middle + A_Center))
		{
			props->inGame = true;
		}
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
	properties->Ending = false;

	int plw, plh;
	properties->Play = H3_Texture_Load("assets/menus/start_start_button.png", &plw, &plh);
	int qlw, qlh;
	properties->Quit = H3_Texture_Load("assets/menus/start_quit_button.png", &qlw, &qlh);
	int ew, eh;
	properties->Retry = H3_Texture_Load("assets/menus/gameover_restart_button.png", &ew, &eh);

	return properties;
}

H3_DEFINE_COMPONENT_PROPERTY_ACCESSORS_RO_EX(MainMenuComponent, MAINMENUCOMPONENT_TYPEID, bool, Ending);
H3_DEFINE_COMPONENT_PROPERTY_ACCESSORS_RO_EX(MainMenuComponent, MAINMENUCOMPONENT_TYPEID, bool, lunching);