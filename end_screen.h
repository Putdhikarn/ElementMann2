#ifndef END_SCREEN_H
#define END_SCREEN_H

#include "game_struct.h"
#include "game_def.h"
#include "audio.h"
#include "control.h"

void LoadEndScreen();
void UnloadEndScreen();
char ProcessEndScreen(double delta);
void DrawEndScreen();

#endif