#include <components/objectscomponent.h>
#include <components/playercomponent.h>
#include <components/bulletscomponent.h>
#include <components/inventorycomponent.h>
#include <Enemie.h>

#include <components/spritecomponent.h>

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

typedef struct
{
	H3Handle scene;
	
	int character; // 1 for man or 2 for woman like on the vital cards

	bool isCatch;
	bool isCashBox;
	EH3Key direction;

	int Tiredness;
	float player_timer;

	bool isGun;
	char strBullets[256];
	int nb_bullets;
	H3Handle Sound_Effect;

	bool isMonster;
	char strMonsters[256];
	int nb_Monsters;

	bool isCoffee;
	char strCoffees[256];
	int nb_Coffees;

	bool isCoin;
	char strCoins[256];
	int nb_Coins;

	bool isPostIt;
	bool isPuzzlePieceSquare;
	bool isPuzzlePieceCircle;
	bool isPuzzlePieceTriangle;
	bool isPuzzlePieceOctogon;
	bool isKey;
	bool isKeyCard;
	bool isBook;

	int inventory_pointer;
	int nb_inventory_objects;

	bool inObject;
	H3Handle object_feet;
	H3Handle object_1, object_2, object_3;
	H3Handle object_tempo;

} PlayerComponent_Properties;

void PlayerComponent_Terminate(void* properties)
{
	free(properties);
}

void PlayerComponent_Update(H3Handle h3, H3Handle object, SH3Transform* transform, float t, float dt, void* properties)
{
	PlayerComponent_Properties* props = (PlayerComponent_Properties*)properties;

	int mouse_x, mouse_y;
	float player_x, player_y;
	int player_velo_x = 0, player_velo_y = 0;

	H3_Input_GetMousePos(h3, &mouse_x, &mouse_y);
	H3_Transform_GetPosition(transform, &player_x, &player_y);


	float center_x, center_y, view_width, view_height, window_width, window_height;
	H3_GetView(h3, &center_x, &center_y, &view_width, &view_height, &window_width, &window_height);

	float x0 = center_x - view_width / 2;
	float y0 = center_y - view_height / 2;
	float x1 = center_x + view_width / 2;
	float y1 = center_y + view_height / 2;

	float mx01 = mouse_x / window_width;
	float my01 = mouse_y / window_height;

	float mxScene = x0 + (x1 - x0) * mx01;
	float myScene = y0 + (y1 - y0) * my01;

	float dx = mxScene - player_x;
	float dy = myScene - player_y;

	float angle = atan2(dy, dx) * H3_RAD2DEG;

	float dist = sqrtf((mxScene - player_x) * (mxScene - player_x) + (myScene - player_y) * (myScene - player_y));


	if (H3_Input_IsKeyDown(K_Z))     props->direction = K_Z;
	else if (H3_Input_IsKeyDown(K_Q))     props->direction = K_Q;
	else if (H3_Input_IsKeyDown(K_S))     props->direction = K_S;
	else if (H3_Input_IsKeyDown(K_D))     props->direction = K_D;
	/*if (H3_Input_IsKeyDown(K_Up))    props->direction = K_Up;
	else if (H3_Input_IsKeyDown(K_Left))  props->direction = K_Left;
	else if (H3_Input_IsKeyDown(K_Down))  props->direction = K_Down;
	else if (H3_Input_IsKeyDown(K_Right)) props->direction = K_Right;*/


	// update position inventory items
	float object_1_x, object_2_x, object_3_x;
	float object_1_y, object_2_y, object_3_y;
	if (props->character == 1)
	{
		object_1_x = player_x - 30, object_1_y = player_y + 230;
		object_2_x = player_x + 30, object_2_y = player_y + 230;
	}
	else if (props->character == 2)
	{
		object_1_x = player_x - 60, object_1_y = player_y + 230;
		object_2_x = player_x, object_2_y = player_y + 230;
		object_3_x = player_x + 60, object_3_y = player_y + 230;
	}

	if (InventoryComponent_Getcase_1Ex(object) != OBJ_Void) H3_Object_SetTranslation(props->object_1, object_1_x, object_1_y);
	if (InventoryComponent_Getcase_2Ex(object) != OBJ_Void) H3_Object_SetTranslation(props->object_2, object_2_x, object_2_y);
	if (InventoryComponent_Getcase_3Ex(object) != OBJ_Void) H3_Object_SetTranslation(props->object_3, object_3_x, object_3_y);


	if (props->Tiredness < 100 && props->isCatch == false)
	{
		// movements
		if (!(H3_Input_IsKeyDown(K_Shift)))
		{
			if (H3_Input_IsKeyDown(K_D) /*|| H3_Input_IsKeyDown(K_Right)*/)
			{
				player_velo_x = 128;
				H3_Object_SetVelocity(object, player_velo_x, player_velo_y);

				H3_Object_RemoveComponent(object, SPRITECOMPONENT_TYPEID);
				H3_Object_AddComponent(object, SPRITECOMPONENT_CREATE("assets/PlayerAndEnemiesSprites/playerright.png", A_Center + A_Middle));
			}
			else if (H3_Input_IsKeyDown(K_Q) /*|| H3_Input_IsKeyDown(K_Left)*/)
			{
				player_velo_x = -128;
				H3_Object_SetVelocity(object, player_velo_x, player_velo_y);

				H3_Object_RemoveComponent(object, SPRITECOMPONENT_TYPEID);
				H3_Object_AddComponent(object, SPRITECOMPONENT_CREATE("assets/PlayerAndEnemiesSprites/playerleft.png", A_Center + A_Middle));
			}
			else
			{
				player_velo_x = 0;
				H3_Object_SetVelocity(object, player_velo_x, player_velo_y);
			}

			if (H3_Input_IsKeyDown(K_Z) /*|| H3_Input_IsKeyDown(K_Up)*/)
			{
				player_velo_y = -128;
				H3_Object_SetVelocity(object, player_velo_x, player_velo_y);

				H3_Object_RemoveComponent(object, SPRITECOMPONENT_TYPEID);
				H3_Object_AddComponent(object, SPRITECOMPONENT_CREATE("assets/PlayerAndEnemiesSprites/playerback.png", A_Center + A_Middle));
			}
			else if (H3_Input_IsKeyDown(K_S) /*|| H3_Input_IsKeyDown(K_Down)*/)
			{
				player_velo_y = 128;
				H3_Object_SetVelocity(object, player_velo_x, player_velo_y);

				H3_Object_RemoveComponent(object, SPRITECOMPONENT_TYPEID);
				H3_Object_AddComponent(object, SPRITECOMPONENT_CREATE("assets/PlayerAndEnemiesSprites/player.png", A_Center + A_Middle));
			}
			else
			{
				player_velo_y = 0;
				H3_Object_SetVelocity(object, player_velo_x, player_velo_y);
			}
		}
		else
		{
			if (H3_Input_IsKeyDown(K_D) /*|| H3_Input_IsKeyDown(K_Right)*/)
			{
				player_velo_x = 282;
				H3_Object_SetVelocity(object, player_velo_x, player_velo_y);

				H3_Object_RemoveComponent(object, SPRITECOMPONENT_TYPEID);
				H3_Object_AddComponent(object, SPRITECOMPONENT_CREATE("assets/PlayerAndEnemiesSprites/playerright.png", A_Center + A_Middle));
			}
			else if (H3_Input_IsKeyDown(K_Q) /*|| H3_Input_IsKeyDown(K_Left)*/)
			{
				player_velo_x = -282;
				H3_Object_SetVelocity(object, player_velo_x, player_velo_y);

				H3_Object_RemoveComponent(object, SPRITECOMPONENT_TYPEID);
				H3_Object_AddComponent(object, SPRITECOMPONENT_CREATE("assets/PlayerAndEnemiesSprites/playerleft.png", A_Center + A_Middle));
			}
			else
			{
				player_velo_x = 0;
				H3_Object_SetVelocity(object, player_velo_x, player_velo_y);
			}

			if (H3_Input_IsKeyDown(K_Z) /*|| H3_Input_IsKeyDown(K_Up)*/)
			{
				player_velo_y = -282;
				H3_Object_SetVelocity(object, player_velo_x, player_velo_y);

				H3_Object_RemoveComponent(object, SPRITECOMPONENT_TYPEID);
				H3_Object_AddComponent(object, SPRITECOMPONENT_CREATE("assets/PlayerAndEnemiesSprites/playerback.png", A_Center + A_Middle));
			}
			else if (H3_Input_IsKeyDown(K_S) /*|| H3_Input_IsKeyDown(K_Down)*/)
			{
				player_velo_y = 282;
				H3_Object_SetVelocity(object, player_velo_x, player_velo_y);

				H3_Object_RemoveComponent(object, SPRITECOMPONENT_TYPEID);
				H3_Object_AddComponent(object, SPRITECOMPONENT_CREATE("assets/PlayerAndEnemiesSprites/player.png", A_Center + A_Middle));
			}
			else
			{
				player_velo_y = 0;
				H3_Object_SetVelocity(object, player_velo_x, player_velo_y);
			}
		}

		// action
		if (H3_Input_IsMouseBtnPressed(MB_Left))
		{
			// attack 
			if (props->isGun == true)
			{
				H3_Sound_Play(props->Sound_Effect, 0.5, false);

				float bullet_x = player_x, bullet_y = player_y;
				float bullet_velo_x = (dx / dist) * 500;
				float bullet_velo_y = (dy / dist) * 500;

				snprintf(props->strBullets, 256, "bullet_%d", props->nb_bullets++);

				H3Handle bullet = H3_Object_Create2(props->scene, props->strBullets, NULL, 7);
				H3_Object_AddComponent(bullet, SPRITECOMPONENT_CREATE("assets/weapons/bullet.png", A_Center + A_Middle));
				H3_Object_AddComponent(bullet, BULLETSCOMPONENT_CREATE());
				H3_Object_EnablePhysics(bullet, H3_BOX_COLLIDER(CDT_Dynamic, 4, 4, 0x22, false));
				H3_Object_SetRotation(bullet, angle);
				H3_Object_SetTranslation(bullet, bullet_x + (bullet_velo_x * 0.07), bullet_y + (bullet_velo_y * 0.07));
				H3_Object_SetVelocity(bullet, bullet_velo_x, bullet_velo_y);
			}

			// energy boost
			else if (props->isCoffee == true)
			{
				props->Tiredness -= 20; // nous donne 60s en plus
				if (props->Tiredness < 0) props->Tiredness = 0;

				if (props->inventory_pointer == 1)
				{
					InventoryComponent_Setcase_1Ex(object, OBJ_Void);
					H3_Object_Destroy(props->object_1, false);
				}
				else if (props->inventory_pointer == 2)
				{
					InventoryComponent_Setcase_2Ex(object, OBJ_Void);
					H3_Object_Destroy(props->object_2, false);
				}
				else if (props->inventory_pointer == 3)
				{
					InventoryComponent_Setcase_3Ex(object, OBJ_Void);
					H3_Object_Destroy(props->object_3, false);
				}

			}
			else if (props->isMonster == true)
			{
				props->Tiredness -= 15; // nous donne 45s en plus
				if (props->Tiredness < 0) props->Tiredness = 0;

				if (props->inventory_pointer == 1)
				{
					InventoryComponent_Setcase_1Ex(object, OBJ_Void);
					H3_Object_Destroy(props->object_1, false);
				}
				else if (props->inventory_pointer == 2)
				{
					InventoryComponent_Setcase_2Ex(object, OBJ_Void);
					H3_Object_Destroy(props->object_2, false);
				}
				else if (props->inventory_pointer == 3)
				{
					InventoryComponent_Setcase_3Ex(object, OBJ_Void);
					H3_Object_Destroy(props->object_3, false);
				}

			}

			//money
			else if ((player_x >= 208 && player_x <= 272) && (player_y >= 1050 && player_y <= 1060))
			{
				//unlock cash box
				if (props->isKeyCard == true)
				{
					props->isCashBox = true;
				}

				// get money
				if (props->isCashBox == true && props->nb_Coins < 5)
				{
					// si tu as un objet, tu le pose par terre
					if (props->nb_inventory_objects != 0)
					{
						if (props->inventory_pointer == 1 && InventoryComponent_Getcase_1Ex(object) != OBJ_Void)
						{
							H3_Object_SetTranslation(props->object_1, player_x, player_y);
							H3_Object_SetRenderOrder(props->object_1, 3);
						}
						else if (props->inventory_pointer == 2 && InventoryComponent_Getcase_2Ex(object) != OBJ_Void)
						{
							H3_Object_SetTranslation(props->object_2, player_x, player_y);
							H3_Object_SetRenderOrder(props->object_2, 3);
						}
						else if (props->inventory_pointer == 3 && InventoryComponent_Getcase_3Ex(object) != OBJ_Void)
						{
							H3_Object_SetTranslation(props->object_3, player_x, player_y);
							H3_Object_SetRenderOrder(props->object_3, 3);
						}
					}

					snprintf(props->strCoins, 256, "coin_%d", props->nb_Coins++);

					H3Handle coin = H3_Object_Create2(props->scene, props->strCoins, NULL, 6);
					H3_Object_EnablePhysics(coin, H3_BOX_COLLIDER(CDT_Dynamic, 22, 22, 0x22, true));
					H3_Object_AddComponent(coin, SPRITECOMPONENT_CREATE("assets/items/coin.png", A_Center + A_Middle));
					H3_Object_AddComponent(coin, OBJECTSCOMPONENT_CREATE(OBJ_coin));

					// tu dis à ton inventaire que tu vas prendre une pièce
					if (props->inventory_pointer == 1)
					{
						InventoryComponent_Setcase_1Ex(object, OBJ_coin);
						props->object_1 = coin;
					}
					else if (props->inventory_pointer == 2)
					{
						InventoryComponent_Setcase_2Ex(object, OBJ_coin);
						props->object_2 = coin;
					}
					else if (props->inventory_pointer == 3)
					{
						InventoryComponent_Setcase_3Ex(object, OBJ_coin);
						props->object_3 = coin;
					}

					props->nb_inventory_objects += 1;
					if (props->character == 1 && props->nb_inventory_objects > 2) props->nb_inventory_objects = 2;
					else if (props->character == 2 && props->nb_inventory_objects > 3) props->nb_inventory_objects = 3;

					// tu prends l'objet
					if (props->character == 1)
					{
						if (props->inventory_pointer == 1)
						{
							H3_Object_SetTranslation(props->object_1, player_x - 30, player_y + 230);
							H3_Object_SetRenderOrder(props->object_1, 6);
						}
						else if (props->inventory_pointer == 2)
						{
							H3_Object_SetTranslation(props->object_2, player_x + 30, player_y + 230);
							H3_Object_SetRenderOrder(props->object_2, 6);
						}
					}
					else if (props->character == 2)
					{
						if (props->inventory_pointer == 1)
						{
							H3_Object_SetTranslation(props->object_1, player_x - 60, player_y + 230);
							H3_Object_SetRenderOrder(props->object_1, 6);
						}
						else if (props->inventory_pointer == 2)
						{
							H3_Object_SetTranslation(props->object_2, player_x, player_y + 230);
							H3_Object_SetRenderOrder(props->object_2, 6);
						}
						else if (props->inventory_pointer == 3)
						{
							H3_Object_SetTranslation(props->object_3, player_x + 60, player_y + 230);
							H3_Object_SetRenderOrder(props->object_3, 6);
						}
					}
				}
			}

			// coin to coffee
			else if (props->isCoin == true && ((player_x >= 2176 && player_x <= 2208) && (player_y >= 316 && player_y <= 330)))
			{
				float coin_x, coin_y;
				snprintf(props->strCoffees, 256, "coffee_%d", props->nb_Coffees++);

				H3Handle coffee = H3_Object_Create2(props->scene, props->strCoffees, NULL, 6);
				H3_Object_EnablePhysics(coffee, H3_BOX_COLLIDER(CDT_Dynamic, 32, 25, 0x22, true));
				H3_Object_AddComponent(coffee, SPRITECOMPONENT_CREATE("assets/items/coffee.png", A_Center + A_Middle));
				H3_Object_AddComponent(coffee, OBJECTSCOMPONENT_CREATE(OBJ_coffee));

				if (props->inventory_pointer == 1)
				{
					H3_Transform_GetPosition(H3_Object_GetTransform(props->object_1), &coin_x, &coin_y);
					InventoryComponent_Setcase_1Ex(object, OBJ_Void);
					H3_Object_Destroy(props->object_1, false);

					H3_Object_SetTranslation(coffee, coin_x, coin_y);

					InventoryComponent_Setcase_1Ex(object, OBJ_coffee);
					props->object_1 = coffee;

				}
				else if (props->inventory_pointer == 2)
				{
					H3_Transform_GetPosition(H3_Object_GetTransform(props->object_2), &coin_x, &coin_y);
					InventoryComponent_Setcase_2Ex(object, OBJ_Void);
					H3_Object_Destroy(props->object_2, false);

					H3_Object_SetTranslation(coffee, coin_x, coin_y);

					InventoryComponent_Setcase_2Ex(object, OBJ_coffee);
					props->object_2 = coffee;

				}
				else if (props->inventory_pointer == 3)
				{
					H3_Transform_GetPosition(H3_Object_GetTransform(props->object_3), &coin_x, &coin_y);
					InventoryComponent_Setcase_3Ex(object, OBJ_Void);
					H3_Object_Destroy(props->object_3, false);

					H3_Object_SetTranslation(coffee, coin_x, coin_y);

					InventoryComponent_Setcase_3Ex(object, OBJ_coffee);
					props->object_3 = coffee;

				}
			}

			// Monster Vending Machine
			else if ((player_x >= 64 && player_x <= 128) && (player_y >= 760 && player_y <= 770))
			{
				// si tu as un objet, tu le pose par terre
				if (props->nb_inventory_objects != 0)
				{
					if (props->inventory_pointer == 1 && InventoryComponent_Getcase_1Ex(object) != OBJ_Void)
					{
						H3_Object_SetTranslation(props->object_1, player_x, player_y);
						H3_Object_SetRenderOrder(props->object_1, 3);
					}
					else if (props->inventory_pointer == 2 && InventoryComponent_Getcase_2Ex(object) != OBJ_Void)
					{
						H3_Object_SetTranslation(props->object_2, player_x, player_y);
						H3_Object_SetRenderOrder(props->object_2, 3);
					}
					else if (props->inventory_pointer == 3 && InventoryComponent_Getcase_3Ex(object) != OBJ_Void)
					{
						H3_Object_SetTranslation(props->object_3, player_x, player_y);
						H3_Object_SetRenderOrder(props->object_3, 3);
					}
				}

				snprintf(props->strMonsters, 256, "coin_%d", props->nb_Monsters++);

				H3Handle monster = H3_Object_Create2(props->scene, props->strMonsters, NULL, 6);
				H3_Object_EnablePhysics(monster, H3_BOX_COLLIDER(CDT_Dynamic, 9, 20, 0x22, true));
				H3_Object_AddComponent(monster, SPRITECOMPONENT_CREATE("assets/items/monster.png", A_Center + A_Middle));
				H3_Object_AddComponent(monster, OBJECTSCOMPONENT_CREATE(OBJ_monster));

				// tu dis à ton inventaire que tu vas prendre une pièce
				if (props->inventory_pointer == 1)
				{
					InventoryComponent_Setcase_1Ex(object, OBJ_monster);
					props->object_1 = monster;
				}
				else if (props->inventory_pointer == 2)
				{
					InventoryComponent_Setcase_2Ex(object, OBJ_monster);
					props->object_2 = monster;
				}
				else if (props->inventory_pointer == 3)
				{
					InventoryComponent_Setcase_3Ex(object, OBJ_monster);
					props->object_3 = monster;
				}

				props->nb_inventory_objects += 1;
				if (props->character == 1 && props->nb_inventory_objects > 2) props->nb_inventory_objects = 2;
				else if (props->character == 2 && props->nb_inventory_objects > 3) props->nb_inventory_objects = 3;

				// tu prends l'objet
				if (props->character == 1)
				{
					if (props->inventory_pointer == 1)
					{
						H3_Object_SetTranslation(props->object_1, player_x - 30, player_y + 230);
						H3_Object_SetRenderOrder(props->object_1, 6);
					}
					else if (props->inventory_pointer == 2)
					{
						H3_Object_SetTranslation(props->object_2, player_x + 30, player_y + 230);
						H3_Object_SetRenderOrder(props->object_2, 6);
					}
				}
				else if (props->character == 2)
				{
					if (props->inventory_pointer == 1)
					{
						H3_Object_SetTranslation(props->object_1, player_x - 60, player_y + 230);
						H3_Object_SetRenderOrder(props->object_1, 6);
					}
					else if (props->inventory_pointer == 2)
					{
						H3_Object_SetTranslation(props->object_2, player_x, player_y + 230);
						H3_Object_SetRenderOrder(props->object_2, 6);
					}
					else if (props->inventory_pointer == 3)
					{
						H3_Object_SetTranslation(props->object_3, player_x + 60, player_y + 230);
						H3_Object_SetRenderOrder(props->object_3, 6);
					}
				}
			}

			//read book
			else if (props->isBook == true)
			{
				;
			}
		}

		if (H3_Input_IsKeyPressed(K_Space))
		{
			// pick up
			if (props->inObject == true)
			{
				props->inObject = false;
				// si tu as un objet, tu le pose par terre
				if (props->nb_inventory_objects != 0)
				{
					if (props->inventory_pointer == 1 && InventoryComponent_Getcase_1Ex(object) != OBJ_Void)
					{
						H3_Object_SetTranslation(props->object_1, player_x, player_y);
						H3_Object_SetRenderOrder(props->object_1, 3);
						props->object_tempo = props->object_1;
						props->inObject = true;
					}
					else if (props->inventory_pointer == 2 && InventoryComponent_Getcase_2Ex(object) != OBJ_Void)
					{
						H3_Object_SetTranslation(props->object_2, player_x, player_y);
						H3_Object_SetRenderOrder(props->object_2, 3);
						props->object_tempo = props->object_2;
						props->inObject = true;
					}
					else if (props->inventory_pointer == 3 && InventoryComponent_Getcase_3Ex(object) != OBJ_Void)
					{
						H3_Object_SetTranslation(props->object_3, player_x, player_y);
						H3_Object_SetRenderOrder(props->object_3, 3);
						props->object_tempo = props->object_3;
						props->inObject = true;
					}
				}

				// tu dis à ton inventaire quel objet on va prendre
				if (props->inventory_pointer == 1)
				{
					InventoryComponent_Setcase_1Ex(object, ObjectsComponent_GetobjectEx(props->object_feet));
					props->object_1 = props->object_feet;
				}
				else if (props->inventory_pointer == 2)
				{
					InventoryComponent_Setcase_2Ex(object, ObjectsComponent_GetobjectEx(props->object_feet));
					props->object_2 = props->object_feet;
				}
				else if (props->inventory_pointer == 3)
				{
					InventoryComponent_Setcase_3Ex(object, ObjectsComponent_GetobjectEx(props->object_feet));
					props->object_3 = props->object_feet;
				}

				props->nb_inventory_objects += 1;
				if (props->character == 1 && props->nb_inventory_objects > 2) props->nb_inventory_objects = 2;
				else if (props->character == 2 && props->nb_inventory_objects > 3) props->nb_inventory_objects = 3;

				// tu prends l'objet
				if (props->character == 1)
				{
					if (props->inventory_pointer == 1)
					{
						H3_Object_SetTranslation(props->object_1, player_x - 30, player_y + 230);
						H3_Object_SetRenderOrder(props->object_1, 6);
					}
					else if (props->inventory_pointer == 2)
					{
						H3_Object_SetTranslation(props->object_2, player_x + 30, player_y + 230);
						H3_Object_SetRenderOrder(props->object_2, 6);
					}
				}
				else if (props->character == 2)
				{
					if (props->inventory_pointer == 1)
					{
						H3_Object_SetTranslation(props->object_1, player_x - 60, player_y + 230);
						H3_Object_SetRenderOrder(props->object_1, 6);
					}
					else if (props->inventory_pointer == 2)
					{
						H3_Object_SetTranslation(props->object_2, player_x, player_y + 230);
						H3_Object_SetRenderOrder(props->object_2, 6);
					}
					else if (props->inventory_pointer == 3)
					{
						H3_Object_SetTranslation(props->object_3, player_x + 60, player_y + 230);
						H3_Object_SetRenderOrder(props->object_3, 6);
					}
				}

				props->object_feet = props->object_tempo;
			}

			// drop
			else if (props->inObject == false)
			{
				if (props->inventory_pointer == 1 && InventoryComponent_Getcase_1Ex(object) != OBJ_Void)
				{
					H3_Object_SetTranslation(props->object_1, player_x, player_y);
					H3_Object_SetRenderOrder(props->object_1, 3);
					props->inObject = true;
					InventoryComponent_Setcase_1Ex(object, OBJ_Void);
					props->object_feet = props->object_1;
					props->object_1 = NULL;
				}
				else if (props->inventory_pointer == 2 && InventoryComponent_Getcase_2Ex(object) != OBJ_Void)
				{
					H3_Object_SetTranslation(props->object_2, player_x, player_y);
					H3_Object_SetRenderOrder(props->object_2, 3);
					props->inObject = true;
					InventoryComponent_Setcase_2Ex(object, OBJ_Void);
					props->object_feet = props->object_2;
					props->object_2 = NULL;
				}
				else if (props->inventory_pointer == 3 && InventoryComponent_Getcase_3Ex(object) != OBJ_Void)
				{
					H3_Object_SetTranslation(props->object_3, player_x, player_y);
					H3_Object_SetRenderOrder(props->object_3, 3);
					props->inObject = true;
					InventoryComponent_Setcase_3Ex(object, OBJ_Void);
					props->object_feet = props->object_3;
					props->object_3 = NULL;
				}
			}
		}

		// inventory
		if (H3_Input_IsKeyPressed(K_Tab))
		{
			props->inventory_pointer += 1;

			if (props->character == 1)
			{
				if (props->inventory_pointer > 2) props->inventory_pointer = 1;
			}
			else if (props->character == 2)
			{
				if (props->inventory_pointer > 3) props->inventory_pointer = 1;
			}
		}

		// boolean management
		if (props->inventory_pointer == 1)
		{
			if (InventoryComponent_Getcase_1Ex(object) == OBJ_airsoft_gun)
			{
				props->isGun = true;
				if (props->direction == K_Z)
				{
					H3_Object_RemoveComponent(object, SPRITECOMPONENT_TYPEID);
					H3_Object_AddComponent(object, SPRITECOMPONENT_CREATE("assets/PlayerAndEnemiesSprites/playerbackgun.png", A_Center + A_Middle));
				}
				else if (props->direction == K_Q)
				{
					H3_Object_RemoveComponent(object, SPRITECOMPONENT_TYPEID);
					H3_Object_AddComponent(object, SPRITECOMPONENT_CREATE("assets/PlayerAndEnemiesSprites/playerleftgun.png", A_Center + A_Middle));
				}
				else if (props->direction == K_S)
				{
					H3_Object_RemoveComponent(object, SPRITECOMPONENT_TYPEID);
					H3_Object_AddComponent(object, SPRITECOMPONENT_CREATE("assets/PlayerAndEnemiesSprites/playerwithgun.png", A_Center + A_Middle));
				}
				else if (props->direction == K_D)
				{
					H3_Object_RemoveComponent(object, SPRITECOMPONENT_TYPEID);
					H3_Object_AddComponent(object, SPRITECOMPONENT_CREATE("assets/PlayerAndEnemiesSprites/playerrightgun.png", A_Center + A_Middle));
				}
			}
			else
			{
				props->isGun = false;
				if (props->direction == K_Z)
				{
					H3_Object_RemoveComponent(object, SPRITECOMPONENT_TYPEID);
					H3_Object_AddComponent(object, SPRITECOMPONENT_CREATE("assets/PlayerAndEnemiesSprites/playerback.png", A_Center + A_Middle));
				}
				else if (props->direction == K_Q)
				{
					H3_Object_RemoveComponent(object, SPRITECOMPONENT_TYPEID);
					H3_Object_AddComponent(object, SPRITECOMPONENT_CREATE("assets/PlayerAndEnemiesSprites/playerleft.png", A_Center + A_Middle));
				}
				else if (props->direction == K_S)
				{
					H3_Object_RemoveComponent(object, SPRITECOMPONENT_TYPEID);
					H3_Object_AddComponent(object, SPRITECOMPONENT_CREATE("assets/PlayerAndEnemiesSprites/player.png", A_Center + A_Middle));
				}
				else if (props->direction == K_D)
				{
					H3_Object_RemoveComponent(object, SPRITECOMPONENT_TYPEID);
					H3_Object_AddComponent(object, SPRITECOMPONENT_CREATE("assets/PlayerAndEnemiesSprites/playerright.png", A_Center + A_Middle));
				}
			}

			if (InventoryComponent_Getcase_1Ex(object) == OBJ_monster) props->isMonster = true;
			else props->isMonster = false;

			if (InventoryComponent_Getcase_1Ex(object) == OBJ_coffee) props->isCoffee = true;
			else props->isCoffee = false;

			if (InventoryComponent_Getcase_1Ex(object) == OBJ_post_it) props->isPostIt = true;
			else props->isPostIt = false;

			if (InventoryComponent_Getcase_1Ex(object) == OBJ_coin) props->isCoin = true;
			else props->isCoin = false;

			if (InventoryComponent_Getcase_1Ex(object) == OBJ_puzzlepiece_square) props->isPuzzlePieceSquare = true;
			else props->isPuzzlePieceSquare = false;

			if (InventoryComponent_Getcase_1Ex(object) == OBJ_puzzlepiece_circle) props->isPuzzlePieceCircle = true;
			else props->isPuzzlePieceCircle = false;

			if (InventoryComponent_Getcase_1Ex(object) == OBJ_puzzlepiece_triangle) props->isPuzzlePieceTriangle = true;
			else props->isPuzzlePieceTriangle = false;

			if (InventoryComponent_Getcase_1Ex(object) == OBJ_puzzlepiece_octogon) props->isPuzzlePieceOctogon = true;
			else props->isPuzzlePieceOctogon = false;

			if (InventoryComponent_Getcase_1Ex(object) == OBJ_key) props->isKey = true;
			else props->isKey = false;

			if (InventoryComponent_Getcase_1Ex(object) == OBJ_keycard) props->isKeyCard = true;
			else props->isKeyCard = false;

			if (InventoryComponent_Getcase_1Ex(object) == OBJ_book) props->isBook = true;
			else props->isBook = false;
		}
		else if (props->inventory_pointer == 2)
		{
			if (InventoryComponent_Getcase_2Ex(object) == OBJ_airsoft_gun)
			{
				props->isGun = true;
				if (props->direction == K_Z)
				{
					H3_Object_RemoveComponent(object, SPRITECOMPONENT_TYPEID);
					H3_Object_AddComponent(object, SPRITECOMPONENT_CREATE("assets/PlayerAndEnemiesSprites/playerbackgun.png", A_Center + A_Middle));
				}
				else if (props->direction == K_Q)
				{
					H3_Object_RemoveComponent(object, SPRITECOMPONENT_TYPEID);
					H3_Object_AddComponent(object, SPRITECOMPONENT_CREATE("assets/PlayerAndEnemiesSprites/playerleftgun.png", A_Center + A_Middle));
				}
				else if (props->direction == K_S)
				{
					H3_Object_RemoveComponent(object, SPRITECOMPONENT_TYPEID);
					H3_Object_AddComponent(object, SPRITECOMPONENT_CREATE("assets/PlayerAndEnemiesSprites/playerwithgun.png", A_Center + A_Middle));
				}
				else if (props->direction == K_D)
				{
					H3_Object_RemoveComponent(object, SPRITECOMPONENT_TYPEID);
					H3_Object_AddComponent(object, SPRITECOMPONENT_CREATE("assets/PlayerAndEnemiesSprites/playerrightgun.png", A_Center + A_Middle));
				}
			}
			else
			{
				props->isGun = false;
				if (props->direction == K_Z)
				{
					H3_Object_RemoveComponent(object, SPRITECOMPONENT_TYPEID);
					H3_Object_AddComponent(object, SPRITECOMPONENT_CREATE("assets/PlayerAndEnemiesSprites/playerback.png", A_Center + A_Middle));
				}
				else if (props->direction == K_Q)
				{
					H3_Object_RemoveComponent(object, SPRITECOMPONENT_TYPEID);
					H3_Object_AddComponent(object, SPRITECOMPONENT_CREATE("assets/PlayerAndEnemiesSprites/playerleft.png", A_Center + A_Middle));
				}
				else if (props->direction == K_S)
				{
					H3_Object_RemoveComponent(object, SPRITECOMPONENT_TYPEID);
					H3_Object_AddComponent(object, SPRITECOMPONENT_CREATE("assets/PlayerAndEnemiesSprites/player.png", A_Center + A_Middle));
				}
				else if (props->direction == K_D)
				{
					H3_Object_RemoveComponent(object, SPRITECOMPONENT_TYPEID);
					H3_Object_AddComponent(object, SPRITECOMPONENT_CREATE("assets/PlayerAndEnemiesSprites/playerright.png", A_Center + A_Middle));
				}
			}

			if (InventoryComponent_Getcase_2Ex(object) == OBJ_monster) props->isMonster = true;
			else props->isMonster = false;

			if (InventoryComponent_Getcase_2Ex(object) == OBJ_coffee) props->isCoffee = true;
			else props->isCoffee = false;

			if (InventoryComponent_Getcase_2Ex(object) == OBJ_post_it) props->isPostIt = true;
			else props->isPostIt = false;

			if (InventoryComponent_Getcase_2Ex(object) == OBJ_coin) props->isCoin = true;
			else props->isCoin = false;

			if (InventoryComponent_Getcase_2Ex(object) == OBJ_puzzlepiece_square) props->isPuzzlePieceSquare = true;
			else props->isPuzzlePieceSquare = false;

			if (InventoryComponent_Getcase_2Ex(object) == OBJ_puzzlepiece_circle) props->isPuzzlePieceCircle = true;
			else props->isPuzzlePieceCircle = false;

			if (InventoryComponent_Getcase_2Ex(object) == OBJ_puzzlepiece_triangle) props->isPuzzlePieceTriangle = true;
			else props->isPuzzlePieceTriangle = false;

			if (InventoryComponent_Getcase_2Ex(object) == OBJ_puzzlepiece_octogon) props->isPuzzlePieceOctogon = true;
			else props->isPuzzlePieceOctogon = false;

			if (InventoryComponent_Getcase_2Ex(object) == OBJ_key) props->isKey = true;
			else props->isKey = false;

			if (InventoryComponent_Getcase_2Ex(object) == OBJ_keycard) props->isKeyCard = true;
			else props->isKeyCard = false;

			if (InventoryComponent_Getcase_2Ex(object) == OBJ_book) props->isBook = true;
			else props->isBook = false;
		}
		else if (props->inventory_pointer == 3)
		{
			if (InventoryComponent_Getcase_3Ex(object) == OBJ_airsoft_gun)
			{
				props->isGun = true;
				if (props->direction == K_Z)
				{
					H3_Object_RemoveComponent(object, SPRITECOMPONENT_TYPEID);
					H3_Object_AddComponent(object, SPRITECOMPONENT_CREATE("assets/PlayerAndEnemiesSprites/playerbackgun.png", A_Center + A_Middle));
				}
				else if (props->direction == K_Q)
				{
					H3_Object_RemoveComponent(object, SPRITECOMPONENT_TYPEID);
					H3_Object_AddComponent(object, SPRITECOMPONENT_CREATE("assets/PlayerAndEnemiesSprites/playerleftgun.png", A_Center + A_Middle));
				}
				else if (props->direction == K_S)
				{
					H3_Object_RemoveComponent(object, SPRITECOMPONENT_TYPEID);
					H3_Object_AddComponent(object, SPRITECOMPONENT_CREATE("assets/PlayerAndEnemiesSprites/playerwithgun.png", A_Center + A_Middle));
				}
				else if (props->direction == K_D)
				{
					H3_Object_RemoveComponent(object, SPRITECOMPONENT_TYPEID);
					H3_Object_AddComponent(object, SPRITECOMPONENT_CREATE("assets/PlayerAndEnemiesSprites/playerrightgun.png", A_Center + A_Middle));
				}
			}
			else
			{
				props->isGun = false;
				if (props->direction == K_Z)
				{
					H3_Object_RemoveComponent(object, SPRITECOMPONENT_TYPEID);
					H3_Object_AddComponent(object, SPRITECOMPONENT_CREATE("assets/PlayerAndEnemiesSprites/playerback.png", A_Center + A_Middle));
				}
				else if (props->direction == K_Q)
				{
					H3_Object_RemoveComponent(object, SPRITECOMPONENT_TYPEID);
					H3_Object_AddComponent(object, SPRITECOMPONENT_CREATE("assets/PlayerAndEnemiesSprites/playerleft.png", A_Center + A_Middle));
				}
				else if (props->direction == K_S)
				{
					H3_Object_RemoveComponent(object, SPRITECOMPONENT_TYPEID);
					H3_Object_AddComponent(object, SPRITECOMPONENT_CREATE("assets/PlayerAndEnemiesSprites/player.png", A_Center + A_Middle));
				}
				else if (props->direction == K_D)
				{
					H3_Object_RemoveComponent(object, SPRITECOMPONENT_TYPEID);
					H3_Object_AddComponent(object, SPRITECOMPONENT_CREATE("assets/PlayerAndEnemiesSprites/playerright.png", A_Center + A_Middle));
				}
			}

			if (InventoryComponent_Getcase_3Ex(object) == OBJ_monster) props->isMonster = true;
			else props->isMonster = false;

			if (InventoryComponent_Getcase_3Ex(object) == OBJ_coffee) props->isCoffee = true;
			else props->isCoffee = false;

			if (InventoryComponent_Getcase_3Ex(object) == OBJ_post_it) props->isPostIt = true;
			else props->isPostIt = false;

			if (InventoryComponent_Getcase_3Ex(object) == OBJ_coin) props->isCoin = true;
			else props->isCoin = false;

			if (InventoryComponent_Getcase_3Ex(object) == OBJ_puzzlepiece_square) props->isPuzzlePieceSquare = true;
			else props->isPuzzlePieceSquare = false;

			if (InventoryComponent_Getcase_3Ex(object) == OBJ_puzzlepiece_circle) props->isPuzzlePieceCircle = true;
			else props->isPuzzlePieceCircle = false;

			if (InventoryComponent_Getcase_3Ex(object) == OBJ_puzzlepiece_triangle) props->isPuzzlePieceTriangle = true;
			else props->isPuzzlePieceTriangle = false;

			if (InventoryComponent_Getcase_3Ex(object) == OBJ_puzzlepiece_octogon) props->isPuzzlePieceOctogon = true;
			else props->isPuzzlePieceOctogon = false;

			if (InventoryComponent_Getcase_3Ex(object) == OBJ_key) props->isKey = true;
			else props->isKey = false;

			if (InventoryComponent_Getcase_3Ex(object) == OBJ_keycard) props->isKeyCard = true;
			else props->isKeyCard = false;

			if (InventoryComponent_Getcase_3Ex(object) == OBJ_book) props->isBook = true;
			else props->isBook = false;
		}

		// tiredness
		if (!(H3_Input_IsKeyDown(K_Shift)))
		{
			if (H3_GetTime() - props->player_timer > 3)
			{
				props->Tiredness++;
				props->player_timer = H3_GetTime();
			}
		}
		else
		{
			if (H3_GetTime() - props->player_timer > 1.5)
			{
				props->Tiredness++;
				props->player_timer = H3_GetTime();
			}
		}

		//printf("player_x = %f and player_y = %f\n", player_x, player_y);
	}

	else if (props->Tiredness >= 100 || props->isCatch == true)
	{
		//STOP
		player_velo_x = 0;
		player_velo_y = 0;
		H3_Object_SetVelocity(object, player_velo_x, player_velo_y);

		if (props->Tiredness >= 100)
		{
			H3_Object_RemoveComponent(object, SPRITECOMPONENT_TYPEID);
			H3_Object_AddComponent(object, SPRITECOMPONENT_CREATE("assets/PlayerAndEnemiesSprites/playerdead.png", A_Center + A_Middle));
		}
	}
}

void PlayerComponent_OnCollisionEnter(H3Handle object, SH3Collision collider)
{
	SH3Component* component = H3_Object_GetComponent(object, PLAYERCOMPONENT_TYPEID);
	PlayerComponent_Properties* props = (PlayerComponent_Properties*)component->properties;

	if (collider.other != NULL && H3_Object_HasComponent(collider.other, ENEMIECOMPONENT_TYPEID))
	{
		props->isCatch = true;
	}
}

void PlayerComponent_OnTriggerEnter(H3Handle object, SH3Collision collider)
{
	SH3Component* component = H3_Object_GetComponent(object, PLAYERCOMPONENT_TYPEID);
	PlayerComponent_Properties* props = (PlayerComponent_Properties*)component->properties;

	if (H3_Object_HasComponent(collider.other, OBJECTSCOMPONENT_TYPEID))
	{
		props->inObject = true;
		props->object_feet = collider.other;
	}
}

void PlayerComponent_OnTriggerLeave(H3Handle object, H3Handle collider)
{
	SH3Component* component = H3_Object_GetComponent(object, PLAYERCOMPONENT_TYPEID);
	PlayerComponent_Properties* props = (PlayerComponent_Properties*)component->properties;

	if (H3_Object_HasComponent(collider, OBJECTSCOMPONENT_TYPEID))
	{
		props->inObject = false;
		props->object_feet = NULL;
	}
}

void* PlayerComponent_CreateProperties(H3Handle scene, int character)
{
	PlayerComponent_Properties* properties = malloc(sizeof(PlayerComponent_Properties));
	H3_ASSERT_CONSOLE(properties, "Failed to allocate properties");

	properties->scene = scene;

	properties->character = character;

	properties->isCatch = false;
	properties->isCashBox = false;

	properties->Tiredness = 0;
	properties->player_timer = 0;

	properties->isGun = false;
	properties->nb_bullets = 0;
	properties->Sound_Effect = H3_Sound_Load("assets/sound_effect_airsoft_shot.wav");

	properties->isMonster = false;
	properties->nb_Monsters = 0;

	properties->isCoffee = false;
	properties->nb_Coffees = 0;

	properties->isCoin = false;
	properties->nb_Coins = 0;

	properties->isPostIt = false;
	properties->isPuzzlePieceSquare = false;
	properties->isPuzzlePieceCircle = false;
	properties->isPuzzlePieceTriangle = false;
	properties->isPuzzlePieceOctogon = false;
	properties->isKey = false;
	properties->isKeyCard = false;

	properties->inventory_pointer = 1;
	properties->nb_inventory_objects = 0;

	properties->inObject = false;
	properties->object_1 = NULL;
	properties->object_2 = NULL;
	properties->object_3 = NULL;
	properties->object_feet = NULL;
	properties->object_tempo = NULL;

	return properties;
}

H3_DEFINE_COMPONENT_PROPERTY_ACCESSORS_RW_EX(PlayerComponent, PLAYERCOMPONENT_TYPEID, int, character);
H3_DEFINE_COMPONENT_PROPERTY_ACCESSORS_RW_EX(PlayerComponent, PLAYERCOMPONENT_TYPEID, int, Tiredness);

H3_DEFINE_COMPONENT_PROPERTY_ACCESSORS_RW_EX(PlayerComponent, PLAYERCOMPONENT_TYPEID, bool, isCatch);