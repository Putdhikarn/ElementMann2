#include "win_screen.h"

static WinScreen winScreen;

void LoadWinScreen() {
    winScreen.panel = LoadTexture("data/sprites/win_panel.png");
    winScreen.passwordDot = LoadTexture("data/sprites/password_dot.png");
    winScreen.bgAnimId = 0;
    winScreen.bgFrame = 0;
}

void ProcessWinScreen() {
    if (IsKeyPressed(CONTROL_CANCEL)) {
        currentGameState = GAME_STATE_LEVEL_SELECT;
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
}

void UnloadWinScreen() {
    UnloadTexture(winScreen.panel);
    UnloadTexture(winScreen.passwordDot);
}
