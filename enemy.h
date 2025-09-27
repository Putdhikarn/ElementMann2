#ifndef ENEMY_H
#define ENEMY_H

#include "game_struct.h"
#include "game_def.h"
#include "map.h"
#include "player.h"
#include "camera.h"

#define MAX_ENEMY_TYPE 1

void LoadEnemyTextures();
Enemy* MakeEnemy(ENEMY_TYPE type, Vector2 pos);
void DoEnemyHit(Enemy *enemy, Vector2 hitPos, int elementType);
void ProcessEnemy(Enemy *enemy, MapData *currentMap, Level *level, float deltaTime);
void DrawEnemy(Enemy *enemy);
void UnloadEnemy(Enemy *enemy);
void UnloadEnemyTextures();

#endif