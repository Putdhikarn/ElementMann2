#ifndef LEVEL_SELECT_H
#define LEVEL_SELECT_H

#include "game_struct.h"
#include "game_def.h"
#include "audio.h"
#include "control.h"

extern char selectedLevel;

void LoadLevelSelect();
void UnloadLevelSelect();
char ProcessLevelSelect(double delta);
void DrawLevelSelect();

#endif