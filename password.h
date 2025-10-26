#ifndef PASSWORD_SELECT_H
#define PASSWORD_SELECT_H

#include "game_struct.h"
#include "game_def.h"
#include "audio.h"
#include "control.h"

extern char selectedLevel;

void LoadPasswordSelect();
void UnloadPasswordSelect();
void ProcessPasswordSelect();
void DrawPasswordSelect();

#endif