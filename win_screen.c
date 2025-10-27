#include "win_screen.h"

static WinScreen winScreen;

void LoadWinScreen() {
    winScreen.panel = LoadTexture("data/sprites/win_panel.png");
    winScreen.passwordDot = LoadTexture("data/sprites/password_dot.png");

    winScreen.elPrev1 = LoadTexture("data/sprites/prev_electric.png");
    winScreen.elPrev2 = LoadTexture("data/sprites/prev_earth.png");
    winScreen.elPrev3 = LoadTexture("data/sprites/prev_water.png");

    winScreen.bgAnimId = 0;
    winScreen.bgFrame = 0;
    winScreen.spriteAnimTimer = 0.0;
}

void ProcessWinScreen(double delta) {
    if (IsKeyPressed(CONTROL_CANCEL)) {
        currentGameState = GAME_STATE_LEVEL_SELECT;
    }
    if (winScreen.spriteAnimTimer >= 0.14){
        winScreen.spriteAnimTimer = 0;
        if (winScreen.spriteAnimateFrame == 3){
            winScreen.spriteAnimateFrame = 0;
        } else {
            winScreen.spriteAnimateFrame++;
        }
    } else {
        winScreen.spriteAnimTimer += delta;
    }
}

void DrawWinScreen() {
    DrawTexture(winScreen.panel, 0 * GAME_TILE_SIZE, 0 * GAME_TILE_SIZE, WHITE);
    if (levelBeat[0]){
        DrawTexture(winScreen.passwordDot, (15 + 0) * GAME_TILE_SIZE, (5 + 4) * GAME_TILE_SIZE, WHITE);
        DrawTexture(winScreen.passwordDot, (15 + 1) * GAME_TILE_SIZE, (5 + 1) * GAME_TILE_SIZE, WHITE);
    }
    if (levelBeat[1]){
        DrawTexture(winScreen.passwordDot, (15 + 0) * GAME_TILE_SIZE, (5 + 3) * GAME_TILE_SIZE, WHITE);
        DrawTexture(winScreen.passwordDot, (15 + 3) * GAME_TILE_SIZE, (5 + 4) * GAME_TILE_SIZE, WHITE);
    }
    if (levelBeat[2]){
        DrawTexture(winScreen.passwordDot, (15 + 4) * GAME_TILE_SIZE, (5 + 3) * GAME_TILE_SIZE, WHITE);
        DrawTexture(winScreen.passwordDot, (15 + 2) * GAME_TILE_SIZE, (5 + 2) * GAME_TILE_SIZE, WHITE);
    }
    if (lastLevel == 0){
        DrawTextureRec(winScreen.elPrev1, (Rectangle){72 * winScreen.spriteAnimateFrame, 0, 72, 72}, (Vector2){5 * GAME_TILE_SIZE, 5 * GAME_TILE_SIZE}, WHITE);
    } else if (lastLevel == 1){
        DrawTextureRec(winScreen.elPrev2, (Rectangle){72 * winScreen.spriteAnimateFrame, 0, 72, 72}, (Vector2){5 * GAME_TILE_SIZE, 5 * GAME_TILE_SIZE}, WHITE);
    } else if (lastLevel == 2){
        DrawTextureRec(winScreen.elPrev3, (Rectangle){72 * winScreen.spriteAnimateFrame, 0, 72, 72}, (Vector2){5 * GAME_TILE_SIZE, 5 * GAME_TILE_SIZE}, WHITE);
    }
}

void UnloadWinScreen() {
    UnloadTexture(winScreen.panel);
    UnloadTexture(winScreen.passwordDot);

    UnloadTexture(winScreen.elPrev1);
    UnloadTexture(winScreen.elPrev2);
    UnloadTexture(winScreen.elPrev3);
}
