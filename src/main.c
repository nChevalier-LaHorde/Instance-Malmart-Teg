#include <h3.h>

#include <components/spritecomponent.h>
#include <components/textcomponent.h>
#include <components/maplayercomponent.h>

#include <components/mycameracomponent.h>
#include <components/playercomponent.h>
#include <components/triggerplayercomponent.h>
#include <components/objectScomponent.h>
#include <components/inventorycomponent.h>
#include <components/clockcomponent.h>
#include <components/tirednesscomponent.h>


#include <math.h>
#include "components/spritecomponent.h"
#include "components/maplayercomponent.h"
#include <components/cameracomponent.h>
#include <components/playercomponent.h>
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
    // Screen + Scene
    const int screen_width = 1920, screen_height = 1080;

    H3Handle screen = H3_Init((SH3InitParams) {
        .width = screen_width,
            .height = screen_height,
            .fullscreen = true,
            .windowTitle = "HorrorMart"
    });

    H3Handle scene = H3_Scene_Create(screen, true);


    // Map
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
    H3_Object_SetRenderOrder(mapobjects, 5);


    // Player
    float player_x = 0, player_y = 0;
    H3Handle player = H3_Object_Create(scene, "Player", NULL);
    H3_Object_AddComponent(player, SPRITECOMPONENT_CREATE("assets/PlayerAndEnemiesSprites/player.png", A_Center + A_Middle));
    H3_Object_AddComponent(player, PLAYERCOMPONENT_CREATE(scene, 1));
    H3_Object_AddComponent(player, INVENTORYCOMPONENT_CREATE());
    H3_Object_EnablePhysics(player, H3_BOX_COLLIDER(CDT_Dynamic, 23, 54, 0x22, false));
    H3_Object_SetTranslation(player, player_x, player_y);
    H3_Object_SetRenderOrder(player, 4);


    // Camera
    H3Handle camera = H3_Object_Create(scene, "camera", NULL);
    H3_Object_AddComponent(camera, MYCAMERACOMPONENT_CREATE(screen_width / 2, screen_height / 2, player));
    H3_Object_SetTranslation(camera, screen_width / 2, screen_height / 2);


    // Inventory
    float inventory_x = player_x, inventory_y = player_y;
    H3Handle inventory = H3_Object_Create(scene, "inventory", NULL);
    /*if      (PlayerComponent_GetcharacterEx == 1)*/ H3_Object_AddComponent(inventory, SPRITECOMPONENT_CREATE("assets/hotbar/hotbar_male.png", A_Center + A_Middle));
    /*else if (PlayerComponent_GetcharacterEx == 2)*/ //H3_Object_AddComponent(inventory, SPRITECOMPONENT_CREATE("assets/hotbar/hotbar_female.png", A_Center + A_Middle));
    H3_Object_SetTranslation(inventory, inventory_x, inventory_y + 230);
    H3_Object_SetRenderOrder(inventory, 6);

    int inventory_pointer_offset;
    int nb_tab = 0;
    if (PlayerComponent_GetcharacterEx(player) == 1) inventory_pointer_offset = -30;
    else if (PlayerComponent_GetcharacterEx(player) == 2) inventory_pointer_offset = -60;
    H3Handle inventory_pointer = H3_Object_Create(scene, "inventory_pointer", NULL);
    H3_Object_AddComponent(inventory_pointer, SPRITECOMPONENT_CREATE("assets/hotbar/hotbar_select.png", A_Center + A_Middle));
    H3_Object_SetTranslation(inventory_pointer, inventory_x + inventory_pointer_offset, inventory_y + 230);
    H3_Object_SetRenderOrder(inventory_pointer, 6);


    // Music
    H3Handle music = H3_Music_Load("assets/Horror_Music.wav");
    H3_Music_Play(music, 1, true);


    // Clock
    H3Handle Clock = H3_Object_Create2(scene, "Clock", camera, 20);
    SH3TextProperties Clock_Props = (SH3TextProperties)
    {
        .font = H3_Font_Load("assets/BOGLEBOLD.otf"),
        .size = 30,
        .fillColor = {.r = 255,.g = 255, .b = 255,.a = 255},
        .anchor = A_Center + A_Middle,
        .hasOutline = true,
        .isBold = false,
        .isItalic = false,
        .isUnderlined = false
    };
    H3_Object_AddComponent(Clock, CLOCKCOMPONENT_CREATE("%dh%d%d", Clock_Props));
    H3_Object_SetTranslation(Clock, 0, -260);


    // Tiredness
    H3Handle Tiredness = H3_Object_Create2(scene, "Tiredness", camera, 20);
    SH3TextProperties Tiredness_Props = (SH3TextProperties)
    {
        .font = H3_Font_Load("assets/BOGLEBOLD.otf"),
        .size = 25,
        .fillColor = {.r = 255,.g = 255, .b = 255,.a = 255},
        .anchor = A_Left + A_Middle,
        .hasOutline = true,
        .isBold = false,
        .isItalic = false,
        .isUnderlined = false
    };
    H3_Object_AddComponent(Tiredness, TIREDNESSCOMPONENT_CREATE("Tiredness : %d/100", Tiredness_Props, player));
    H3_Object_SetTranslation(Tiredness, -470, -260);


    //object test
    H3Handle airsoft_gun = H3_Object_Create(scene, "airsoft_gun", NULL);
    H3_Object_EnablePhysics(airsoft_gun, H3_BOX_COLLIDER(CDT_Dynamic, 9, 20, 0x22, true));
    H3_Object_AddComponent(airsoft_gun, SPRITECOMPONENT_CREATE("assets/items/airsoft.png", A_Center + A_Middle));
    H3_Object_AddComponent(airsoft_gun, OBJECTSCOMPONENT_CREATE(OBJ_airsoft_gun));
    H3_Object_SetTranslation(airsoft_gun, 1552, 957);
    H3_Object_SetRenderOrder(airsoft_gun, 6);

    H3Handle keycard_test = H3_Object_Create(scene, "keycard_test", NULL);
    H3_Object_EnablePhysics(keycard_test, H3_BOX_COLLIDER(CDT_Dynamic, 9, 20, 0x22, true));
    H3_Object_AddComponent(keycard_test, SPRITECOMPONENT_CREATE("assets/items/keycard.png", A_Center + A_Middle));
    H3_Object_AddComponent(keycard_test, OBJECTSCOMPONENT_CREATE(OBJ_keycard));
    H3_Object_SetTranslation(keycard_test, 1952, 621);
    H3_Object_SetRenderOrder(keycard_test, 5);

    H3Handle book_test = H3_Object_Create(scene, "book_test", NULL);
    H3_Object_EnablePhysics(book_test, H3_BOX_COLLIDER(CDT_Dynamic, 9, 20, 0x22, true));
    H3_Object_AddComponent(book_test, SPRITECOMPONENT_CREATE("assets/items/bookS.png", A_Center + A_Middle));
    H3_Object_AddComponent(book_test, OBJECTSCOMPONENT_CREATE(OBJ_book));
    H3_Object_SetTranslation(book_test, 3792, 752);
    H3_Object_SetRenderOrder(book_test, 5);


    //MENU BEGINNING
    H3Handle BackGroudB = H3_Object_Create2(scene, "BackGroud", NULL, 100);
    H3_Object_AddComponent(BackGroudB, SPRITECOMPONENT_CREATE("assets/menus/start.png", A_Middle + A_Center));
    H3_Object_AddComponent(BackGroudB, MAINMENUCOMPONENT_CREATE(player));
    H3_Object_SetTranslation(BackGroudB, 0, 0);

    //MENU ENDING
    H3Handle BackGroudE = H3_Object_Create2(scene, "BackGroud", NULL, 100);
    H3_Object_AddComponent(BackGroudE, SPRITECOMPONENT_CREATE("assets/menus/gameover.png", A_Middle + A_Center));
    H3_Object_AddComponent(BackGroudE, MAINMENUCOMPONENT_CREATE(player));
    H3_Object_SetTranslation(BackGroudE, -1000, -1000);

    //ENIGME EQUATION
    H3Handle EnigmeEquation = H3_Object_Create2(scene, "EnigmeEquation", NULL, 12);
    H3_Object_AddComponent(EnigmeEquation, EQUATIONCOMPONENT_CREATE(scene, player));

    //ENIGMESHAPE
    H3Handle EnigmeShape = H3_Object_Create2(scene, "EnigmeShape", NULL, 12);
    H3_Object_AddComponent(EnigmeShape, ENIGMESHAPECOMPONENT_CREATE(scene));

    //ENIGMEBUTTON
    H3Handle EnigmeButton = H3_Object_Create2(scene, "EnigmeButton", NULL, 12);
    H3_Object_AddComponent(EnigmeButton, COFEECOMPONENT_CREATE(scene, player));

    //ENIGMEWIRE
    H3Handle EnigmeWire = H3_Object_Create2(scene, "EnigmeWire", NULL, 12);
    H3_Object_AddComponent(EnigmeWire, WIRECOMPONENT_CREATE(scene, player));

    //CHAMP DE VISION
    H3Handle Vision = H3_Object_Create(scene, "vision", player);
    H3_Object_AddComponent(Vision, SPRITECOMPONENT_CREATE("assets/ChampDeVision.png", A_Center + A_Middle));
    H3_Object_SetRenderOrder(Vision, 5);


    int EnemieCounteBoss = 1;
    int EnemieCounteMinion = 1;
    char strEnemie[256];
    int enemieindex = 0;
    float TimerBoss = H3_GetTime();
    float Timer = H3_GetTime();


    bool keepGoing = true;
    while (keepGoing)
    {
        float SpawnRndx = (rand() % 1481) + 418;
        float SpawnRndy = (rand() % 735) + 764;

        H3_Transform_GetPosition(H3_Object_GetTransform(player), &inventory_x, &inventory_y);
        H3_Object_SetTranslation(inventory, inventory_x, inventory_y + 230);
        H3_Object_SetTranslation(inventory_pointer, inventory_x + inventory_pointer_offset, inventory_y + 230);

        if (PlayerComponent_GetisCatchEx(player) == false && PlayerComponent_GetTirednessEx(player) < 100)
        {
            if (H3_Input_IsKeyPressed(K_Tab))
            {
                nb_tab += 1;
                if (PlayerComponent_GetcharacterEx(player) == 1) inventory_pointer_offset = -inventory_pointer_offset;
                else if (PlayerComponent_GetcharacterEx(player) == 2)
                {
                    if (nb_tab % 3 == 0) inventory_pointer_offset = -60;
                    else if (nb_tab % 3 == 1) inventory_pointer_offset = 0;
                    else if (nb_tab % 3 == 2) inventory_pointer_offset = 60;
                }
            }
        }


        //BACKGROUD

        if (MainMenuComponent_GetlunchingEx == false)
        {
            H3_Object_RemoveComponent(BackGroudB, SPRITECOMPONENT_TYPEID);
            H3_Object_RemoveComponent(BackGroudB, MAINMENUCOMPONENT_TYPEID);

        }
        if (MainMenuComponent_GetEndingEx == true)
        {
            H3_Object_RemoveComponent(BackGroudE, SPRITECOMPONENT_TYPEID);
            H3_Object_RemoveComponent(BackGroudE, MAINMENUCOMPONENT_TYPEID);
        }
        //ENEMIE
        if (EnemieCounteBoss <= 1)
        {
            if (H3_GetTime() - Timer >= 5)
            {
                H3Handle Boss = H3_Object_Create(scene, "Boss", NULL);
                H3_Object_EnablePhysics(Boss, H3_BOX_COLLIDER(CDT_Dynamic, 54, 60, 0x22, false));
                H3_Object_AddComponent(Boss, SPRITECOMPONENT_CREATE("assets/PlayerAndEnemiesSprites/miniboss.png", A_Center + A_Middle));
                H3_Object_AddComponent(Boss, ENEMIECOMPONENT_CREATE(player, scene, 20));
                H3_Object_SetTranslation(Boss, 2670, 485);
                H3_Object_SetRenderOrder(Boss, 4);
                EnemieCounteBoss += 1;
                TimerBoss = H3_GetTime();
            }
        }
        //if (EnemieCounteMinion <= 5)
        //{

        //    if (h3_gettime() - Timer >= 1) 
        //    {
        //        snprintf(strEnemie, 256, "enemie_%d", enemieindex++);
        //        H3Handle enemie = H3_Object_Create(scene, strEnemie, NULL);
        //        H3_Object_EnablePhysics(enemie, H3_BOX_COLLIDER(CDT_Dynamic, 54, 60, 0x22, false));
        //        H3_Object_AddComponent(enemie, SPRITECOMPONENT_CREATE("assets/playerandenemiessprites/enemie.png", A_Center + A_Middle));
        //        H3_Object_AddComponent(enemie, ENEMIECOMPONENT_CREATE(player, scene, 5));
        //        H3_Object_SetRenderOrder(enemie, 4);
        //        H3_Object_SetTranslation(enemie, 1450, 950);
        //        EnemieCounteMinion += 1;
        //        Timer = h3_gettime();
        //        
        //        
        //       /* if (EnemieCounteMinion <= 10 && EnemieCounteMinion >=5)
        //        {
        //            H3_Object_SetTranslation(enemie, 1500, 1035);
        //        }
        //        if (enemiecounteminion <= 15 && enemiecounteminion >= 10)
        //        {
        //            h3_object_settranslation(enemie, 2670, 485);
        //        }*/
        //    }
        //}


        keepGoing = H3_DoFrame(screen, scene);
    }
}
