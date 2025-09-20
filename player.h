#ifndef PLAYER_H
#define PLAYER_H

#include "include/raylib.h"
#include "level.h"
#include "projectile.h"
#include "sprite.h"
#include "map.h"
#include "control.h"
#include "game_def.h"
#include "game_struct.h"
#include <stdlib.h>

Player* LoadPlayer(float topLeftX, float topLeftY);
void ProcessPlayer(Player *player, MapData *currentMap, Level *currentLevel, float deltaTime);
void ApplyPlayerVelocity(Player *player, MapData *currentMap, float deltaTime);
int checkPlayerOnGround(Player *player, MapData *currentMap);
void AnimatePlayerSprite(Player *player, float deltaTime);
void DoPlayerHit(Player *player, Vector2 hitPos);
void DrawPlayer(Player *player);
void UnloadPlayer(Player *player);

#endif