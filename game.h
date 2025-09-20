#ifndef GAME_H
#define GAME_H

#include "include/raylib.h"
#include "game_def.h"
#include "game_struct.h"
#include "projectile.h"
#include "level.h"
#include "enemy.h"
#include "map.h"
#include "player.h"
#include <stdio.h>

#define PIXEL_SCALE_FACTOR 3.0

void GameInit();
void GameLoop();
void GameCleanUp();

#endif