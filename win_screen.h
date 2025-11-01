#ifndef WIN_SCREEN_H
#define WIN_SCREEN_H

#include "game_struct.h"
#include "audio.h"
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

    Texture2D elPrev1;
    Texture2D elPrev2;
    Texture2D elPrev3;

    int bgAnimId;
    int bgFrame;
    int spriteAnimateFrame;
    double spriteAnimTimer;
} WinScreen;

void LoadWinScreen();
void ProcessWinScreen(double delta);
void DrawWinScreen();
void UnloadWinScreen();

#endif
