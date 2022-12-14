#include <h3.h>

#include <components/spritecomponent.h>
#include <components/textcomponent.h>
#include <components/maplayercomponent.h>

#include <components/mycameracomponent.h>
#include <components/playercomponent.h>
#include <components/triggerplayercomponent.h>
#include <components/objectScomponent.h>
#include <components/inventorycomponent.h>


#ifndef NDEBUG
# pragma comment(lib, "h3-s-d.lib")
#else // !NDEBUG
# pragma comment(lib, "h3-s.lib")
#endif // !NDEBUG

int main(int argc, char** argv)
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
    float player_x = 49, player_y = 847;
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
    H3_Object_SetRenderOrder(inventory, 5);


    int inventory_pointer_offset;
    int nb_tab = 0;
    if      (PlayerComponent_GetcharacterEx(player) == 1) inventory_pointer_offset = -30;
    else if (PlayerComponent_GetcharacterEx(player) == 2) inventory_pointer_offset = -60;
    H3Handle inventory_pointer = H3_Object_Create(scene, "inventory_pointer", NULL);
    H3_Object_AddComponent(inventory_pointer, SPRITECOMPONENT_CREATE("assets/hotbar/hotbar_select.png", A_Center + A_Middle));
    H3_Object_SetTranslation(inventory_pointer, inventory_x + inventory_pointer_offset, inventory_y + 230);
    H3_Object_SetRenderOrder(inventory_pointer, 5);

    // Music
    H3Handle music = H3_Music_Load("assets/Horror_Music.wav");
    H3_Music_Play(music, 1, true);


    //object test
    H3Handle airsoft_gun = H3_Object_Create(scene, "airsoft_gun", NULL);
    H3_Object_EnablePhysics(airsoft_gun, H3_BOX_COLLIDER(CDT_Dynamic, 9, 20, 0x22, true));
    H3_Object_AddComponent(airsoft_gun, SPRITECOMPONENT_CREATE("assets/items/airsoft.png", A_Center + A_Middle));
    H3_Object_AddComponent(airsoft_gun, OBJECTSCOMPONENT_CREATE(OBJ_airsoft_gun));
    H3_Object_SetTranslation(airsoft_gun, 1552, 957);
    H3_Object_SetRenderOrder(airsoft_gun, 6);

    bool keepGoing = true;
    while (keepGoing)
    {
        H3_Transform_GetPosition(H3_Object_GetTransform(player), &inventory_x, &inventory_y);
        H3_Object_SetTranslation(inventory, inventory_x, inventory_y + 230);
        H3_Object_SetTranslation(inventory_pointer, inventory_x + inventory_pointer_offset, inventory_y + 230);

        if (H3_Input_IsKeyPressed(K_Tab))
        {
            nb_tab += 1;
            if      (PlayerComponent_GetcharacterEx(player) == 1) inventory_pointer_offset = -inventory_pointer_offset;
            else if (PlayerComponent_GetcharacterEx(player) == 2)
            {
                if      (nb_tab % 3 == 0) inventory_pointer_offset = -60;
                else if (nb_tab % 3 == 1) inventory_pointer_offset =   0;
                else if (nb_tab % 3 == 2) inventory_pointer_offset =  60;
            }
        }

        
        keepGoing = H3_DoFrame(screen, scene);
    }
	return 0;
}
