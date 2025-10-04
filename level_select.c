#include "level_select.h"

char selectCursorX = 0;
char selectCursorY = 0;

Texture levelSelectText;
Texture levelSelectCursor;
Texture levelIcon1;
Texture levelIcon1G;
Texture levelIcon2;
Texture levelIcon2G;
Texture levelIcon3;
Texture levelIcon3G;
Texture levelIcon4;
Texture levelIcon4G;
// Texture dummy2; // another dummy to fix the bug

void LoadLevelSelect(){
    levelSelectText = LoadTexture("./data/sprites/level_select.png");
    levelSelectCursor = LoadTexture("./data/sprites/select_cursor.png");

    levelIcon1 = LoadTexture("./data/sprites/stage1.png");
    levelIcon1G = LoadTexture("./data/sprites/stage1g.png");
    levelIcon2 = LoadTexture("./data/sprites/stage1.png");
    levelIcon2G = LoadTexture("./data/sprites/stage1g.png");
    levelIcon3 = LoadTexture("./data/sprites/stage1.png");
    levelIcon3G = LoadTexture("./data/sprites/stage1g.png");
    levelIcon4 = LoadTexture("./data/sprites/stage1.png");
    levelIcon4G = LoadTexture("./data/sprites/stage1g.png");
}

void UnloadLevelSelect(){
    UnloadTexture(levelSelectText);
    UnloadTexture(levelSelectCursor);

    UnloadTexture(levelIcon1);
    UnloadTexture(levelIcon1G);
    UnloadTexture(levelIcon2);
    UnloadTexture(levelIcon2G);
    UnloadTexture(levelIcon3);
    UnloadTexture(levelIcon3G);
    UnloadTexture(levelIcon4);
    UnloadTexture(levelIcon4G);
}

void ProcessLevelSelect(){
    if (IsKeyPressed(CONTROL_UP)){
        selectCursorY = 1;
    } else if (IsKeyPressed(CONTROL_DOWN)){
        selectCursorY = 0;
    } else if (IsKeyPressed(CONTROL_LEFT)){
        if (selectCursorX > 0){
            selectCursorX--;
        }
    } else if (IsKeyPressed(CONTROL_RIGHT)){
        if (selectCursorX < 2){
            selectCursorX++;
        }
    } else if (IsKeyPressed(CONTROL_CANCEL)){
        currentGameState = GAME_STATE_LEVEL;
    }
}

void DrawLevelSelect(){
    DrawTexture(levelSelectText, 7 * GAME_TILE_SIZE, GAME_TILE_SIZE, WHITE);
    DrawTexture(levelIcon1, 5 * GAME_TILE_SIZE, 8 * GAME_TILE_SIZE, WHITE);
    DrawTexture(levelIcon2, 11 * GAME_TILE_SIZE, 8 * GAME_TILE_SIZE, WHITE);
    DrawTexture(levelIcon3, 17 * GAME_TILE_SIZE, 8 * GAME_TILE_SIZE, WHITE);
    DrawTexture(levelIcon4, 11 * GAME_TILE_SIZE, 3 * GAME_TILE_SIZE, WHITE);
    if (selectCursorY == 1){
        DrawTexture(levelSelectCursor, 11 * GAME_TILE_SIZE, 3 * GAME_TILE_SIZE, WHITE);
    } else {
        DrawTexture(levelSelectCursor, (5 + (6 * selectCursorX)) * GAME_TILE_SIZE, 8 * GAME_TILE_SIZE, WHITE);
    }
}
