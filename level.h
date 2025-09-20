#ifndef LEVEL_H
#define LEVEL_H

#include "include/raylib.h"
#include "game_struct.h"
#include "projectile.h"
#include "enemy.h"


Level* LoadLevel(Camera2D *camera);
void UnloadLevel(Level *level);

void AddProjectile(Level *level, Projectile *toAdd);

void ProcessLevelProjectile(Level *level, MapData *mapData, float deltaTime);
void DrawLevelProjectile(Level *level);

void CleanUpProjectile(Level *level);

void AddEnemy(Level *level, Enemy *toAdd);
void ProcessLevelEnemy(Level *level, MapData *mapData, float deltaTime);
void DrawLevelEnemy(Level *level);
void CleanUpEnemy(Level *level);

#endif