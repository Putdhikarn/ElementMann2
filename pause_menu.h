#ifndef PAUSE_MENU_H
#define PAUSE_MENU_H

#include "game_struct.h"
#include "game_def.h"
#include "audio.h"
#include "control.h"

void ResetPauseMenu();
void LoadPauseMenu();
void UnloadPauseMenu();

void ProcessPauseMeun(Player* player);
void DrawPauseMenu(Player* player);

extern Texture elementBar2;
extern Texture elementBar3;
extern Texture elementBar4;

#endif