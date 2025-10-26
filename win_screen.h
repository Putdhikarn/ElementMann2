#ifndef WIN_SCREEN_H
#define WIN_SCREEN_H

#include "game_struct.h"
#include "control.h"
#include "game_def.h"
#include "include/raylib.h"
#include "game_struct.h"

typedef struct {
    Texture2D panel;
    Texture2D passwordDot;
    Texture2D water;
    Texture2D fire;
    Texture2D grass;

    int bgAnimId;
    int bgFrame;
    int spriteAnimateFrame;
    int moveSpriteAnimId;
    int lastMoveSpriteAnimId;
} WinScreen;

void LoadWinScreen();
void ProcessWinScreen();
void DrawWinScreen();
void UnloadWinScreen();

#endif
