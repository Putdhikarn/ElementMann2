#include "main_menu.h"

char mainMenuCursorPos = 0;

char titleBounceState = 0;
double titleBounce = 0;

Texture passwordText;
Texture title;
Texture titleBG;
Texture cursor;
Texture startText;
Texture dummyTextureThatSomehowfixTheTextureStrechingBug;

void LoadMainMenu(){
    title = LoadTexture("data/sprites/title.png");
    titleBG = LoadTexture("data/sprites/bg.png");
    cursor = LoadTexture("data/sprites/cursor.png");
    passwordText = LoadTexture("data/sprites/password_text2.png");
    startText = LoadTexture("data/sprites/start_text.png");
}

void UnloadMainMenu(){
    UnloadTexture(title);
    UnloadTexture(titleBG);
    UnloadTexture(cursor);
    UnloadTexture(startText);
    UnloadTexture(passwordText);
}

void ProcessMainMenu(double delta){
    if (titleBounce >= 0.3409){
        titleBounceState = titleBounceState ? 0 : 1;
        titleBounce = 0;
    } else {
        titleBounce += delta;
    }
    if (IsKeyPressed(CONTROL_CANCEL)){
        if (mainMenuCursorPos == 1){
            currentGameState = GAME_STATE_PASSWORD;
            PlaySFX(SFX_CURSOR);
            PlayBGM(BGM_PASSWORD);
        } else {
            currentGameState = GAME_STATE_LEVEL_SELECT;
            PlaySFX(SFX_CURSOR);
            PlayBGM(BGM_SELECT);
        }
    }
    if (IsKeyPressed(CONTROL_UP) && mainMenuCursorPos != 0){
        mainMenuCursorPos = 0;
        PlaySFX(SFX_CURSOR);
    } else if (IsKeyPressed(CONTROL_DOWN) && mainMenuCursorPos != 1){
        mainMenuCursorPos = 1;
        PlaySFX(SFX_CURSOR);
    }
}

void DrawMainMeun(){
    DrawTexture(titleBG, 0, 0, WHITE);
    DrawTexture(title, (5 * GAME_TILE_SIZE), ((GAME_TILE_SIZE / 2) * titleBounceState) + GAME_TILE_SIZE, WHITE);
    DrawTexture(cursor, (6 * GAME_TILE_SIZE), (8 + (mainMenuCursorPos * 2)) * GAME_TILE_SIZE, WHITE);
    DrawTexture(startText, (8 * GAME_TILE_SIZE), 8 * GAME_TILE_SIZE, WHITE);
    DrawTexture(passwordText, (8 * GAME_TILE_SIZE), 10 * GAME_TILE_SIZE, WHITE);
}