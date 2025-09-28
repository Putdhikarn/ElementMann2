#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "include/raylib.h"
#include "game_def.h"
#include "game_struct.h"
#include "enemy.h"

#define MAX_PROJECTILE_TYPE 64

void LoadProjectileTextures();
Projectile* MakeProjectile(PROJ_TYPE type, Vector2 pos, Vector2 velocity, Vector2 hitBoxSize, Vector2 hitBoxOffset, int facing);
void ProcessProjectile(Projectile *projectile, MapData *currentMap, Level *level, float deltaTime);
void DrawProjectile(Projectile *projectile);
void UnloadProjectile(Projectile *projectile);
void UnloadProjectileTextures();

#endif