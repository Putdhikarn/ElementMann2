#ifndef WIN_SCREEN_H
#define WIN_SCREEN_H

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

void WinScreen_Init(WinScreen *ws);
void WinScreen_Update(WinScreen *ws);
void WinScreen_Draw(WinScreen *ws, Level *level);
void WinScreen_Unload(WinScreen *ws);

void LoadWinScreen();
void ProcessWinScreen();
void DrawWinScreen();
void UnloadWinScreen();

#endif
