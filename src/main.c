#include <h3.h>
#include <math.h>
#include "components/spritecomponent.h"
#include "components/maplayercomponent.h"
#include <components/cameracomponent.h>
//#include <animatedspritecomponent.h>
#include "Player.h"
#include "Enemie.h"
#include "Detector.h"
#include "EnigmeShape.h"
#include "Cofee.h"
#include "Wire.h"
#include "Equation.h"
#include "MainMenu.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#ifndef NDEBUG
# pragma comment(lib, "h3-s-d.lib")
#else // !NDEBUG
# pragma comment(lib, "h3-s.lib")
#endif // !NDEBUG=======


int main()
{
	float px;
	float py;
	int EnemieCounte = 1;
	char enemie[256];
	int enemieindex = 0;
	float Timer = H3_GetTime();


	H3Handle h3 = H3_Init((SH3InitParams) {
		.width = 1920,
		.height = 960,
		.fullscreen = false,
		.windowTitle = "Pandemie"
	});


	H3Handle scene = H3_Scene_Create(h3, false);

	bool En_cours = true;

	H3Handle Camera = H3_Object_Create(scene, "Camera", NULL);
	H3_Object_AddComponent(Camera, CAMERACOMPONENT_CREATE(960, 480));


	//PLAYER
	H3Handle Player = H3_Object_Create(scene, "Player", NULL);
	H3_Object_EnablePhysics(Player, H3_BOX_COLLIDER(CDT_Dynamic, 26, 45, 0x22, false));
	H3_Object_AddComponent(Player, SPRITECOMPONENT_CREATE("assets/PlayerAndEnemiesSprites/player.png", A_Center + A_Middle));
	H3_Object_AddComponent(Player, PLAYERCOMPONENT_CREATE(scene));
	H3_Object_SetTranslation(Player, -1000, -1000);
	H3_Object_SetRenderOrder(Player, 3);
	
	//MENU
	H3Handle BackGroud = H3_Object_Create2(scene, "BackGroud", NULL, 100);
	H3_Object_AddComponent(BackGroud, SPRITECOMPONENT_CREATE("assets/menus/start.png", A_Middle + A_Center));
	H3_Object_AddComponent(BackGroud, MAINMENUCOMPONENT_CREATE(Player));
	
	//ENIGME EQUATION
	H3Handle EnigmeEquation = H3_Object_Create2(scene, "EnigmeEquation", NULL, 12);
	H3_Object_AddComponent(EnigmeEquation, EQUATIONCOMPONENT_CREATE(scene, Player));

	//ENIGMESHAPE
	H3Handle EnigmeShape = H3_Object_Create2(scene, "EnigmeShape", NULL, 12);
	H3_Object_AddComponent(EnigmeShape, ENIGMESHAPECOMPONENT_CREATE(scene));

	//ENIGMEBUTTON
	H3Handle EnigmeButton = H3_Object_Create2(scene, "EnigmeButton", NULL, 12);
	H3_Object_AddComponent(EnigmeButton, COFEECOMPONENT_CREATE(scene, Player));

	//ENIGMEWIRE
	H3Handle EnigmeWire = H3_Object_Create2(scene, "EnigmeWire", NULL, 12);
	H3_Object_AddComponent(EnigmeWire, WIRECOMPONENT_CREATE(scene, Player));

	//CHAMP DE VISION
	H3Handle Vision = H3_Object_Create(scene, "vision", Player);
	H3_Object_AddComponent(Vision, SPRITECOMPONENT_CREATE("assets/ChampDeVision.png", A_Center + A_Middle));
	H3_Object_SetRenderOrder(Vision, 10);

	//MAP
	H3Handle map_load = H3_Map_Load("assets/maps/realmap.tmx");
	H3_Map_RegisterObjectLayerForPhysicsInScene(scene, map_load, "collider");
	H3Handle mapfloor = H3_Object_Create(scene, "mapfloor", NULL);
	H3_Object_AddComponent(mapfloor, MAPLAYERCOMPONENT_CREATE(map_load, "floor"));
	H3_Object_SetRenderOrder(mapfloor, 1);
	H3Handle mapwalls = H3_Object_Create(scene, "mapwalls", NULL);
	H3_Object_AddComponent(mapwalls, MAPLAYERCOMPONENT_CREATE(map_load, "walls"));
	H3_Object_SetRenderOrder(mapwalls, 2);
	H3Handle mapobjects = H3_Object_Create(scene, "mapobjects", NULL);
	H3_Object_AddComponent(mapobjects, MAPLAYERCOMPONENT_CREATE(map_load, "objects"));
	H3_Object_SetRenderOrder(mapobjects, 4);
	
	do
	{
		H3_Transform_GetPosition(H3_Object_GetTransform(Player), &px, &py);

		//BACKGROUD
		H3_Object_SetTranslation(BackGroud, px, py);
		if (px >= 1 && py >= 1)
		{
			H3_Object_RemoveComponent(BackGroud, SPRITECOMPONENT_TYPEID);
			H3_Object_RemoveComponent(BackGroud, MAINMENUCOMPONENT_TYPEID);
		}

		//CAMERA UPDTAE
		H3_Object_SetTranslation(Camera, px, py);

		//VISION UPDATE
		//H3_Object_SetTranslation(Vision, px, py);

		//ENEMIE
		if (EnemieCounte <= 1)
		{

			if (H3_GetTime() - Timer >= 5)
			{
				enemieindex += 1;
				snprintf(enemie, 256, "Enemie_%d", enemieindex);
				H3Handle Enemie = H3_Object_Create(scene, enemie, NULL);
				H3_Object_EnablePhysics(Enemie, H3_BOX_COLLIDER(CDT_Dynamic, 54, 60, 0x22, false));
				H3_Object_AddComponent(Enemie, SPRITECOMPONENT_CREATE("assets/PlayerAndEnemiesSprites/miniboss.png", A_Center + A_Middle));
				H3_Object_AddComponent(Enemie, ENEMIECOMPONENT_CREATE(Player, scene));
				H3_Object_SetTranslation(Enemie, 400, 400);
				H3_Object_SetRenderOrder(Enemie, 4);
				EnemieCounte += 1;
				printf("%d\n", EnemieCounte);
				Timer = H3_GetTime();
			}
		}
		

		En_cours = H3_DoFrame(h3, scene);
	} while (En_cours);

	return 0;
}

//3730 33745