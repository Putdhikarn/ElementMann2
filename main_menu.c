#include "main_menu.h"

char cursor_pos = 0;

Texture passwordText;
Texture title;
Texture titleBG;
Texture cursor;
Texture startText;
Texture dummyTextureThatSomehowfixTheTextureStrechingBug;

void LoadMainMenu(){
    title = LoadTexture("./data/sprites/title.png");
    //titleBG = LoadTexture("./data/sprites/title.png");
    cursor = LoadTexture("./data/sprites/cursor.png");
    passwordText = LoadTexture("./data/sprites/password_text2.png");
    startText = LoadTexture("./data/sprites/start_text.png");
}

void UnloadMainMenu(){
    UnloadTexture(title);
    //UnloadTexture(titleBG);
    UnloadTexture(cursor);
    UnloadTexture(startText);
    UnloadTexture(passwordText);
}

void ProcessMainMenu(){
    if (IsKeyPressed(CONTROL_CANCEL)){
        if (cursor_pos == 1){
            currentGameState = GAME_STATE_PASSWORD;
        } else {
            currentGameState = GAME_STATE_LEVEL_SELECT;
        }
    }
    if (IsKeyPressed(CONTROL_UP)){
        cursor_pos = 0;
    } else if (IsKeyPressed(CONTROL_DOWN)){
        cursor_pos = 1;
    }
}

void DrawMainMeun(){
    DrawTexture(title, (5 * GAME_TILE_SIZE), GAME_TILE_SIZE, WHITE);
    DrawTexture(cursor, (6 * GAME_TILE_SIZE), (7 + (cursor_pos * 2)) * GAME_TILE_SIZE, WHITE);
    DrawTexture(startText, (8 * GAME_TILE_SIZE), 7 * GAME_TILE_SIZE, WHITE);
    DrawTexture(passwordText, (8 * GAME_TILE_SIZE), 9 * GAME_TILE_SIZE, WHITE);
}