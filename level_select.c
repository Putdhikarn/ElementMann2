#include "level_select.h"

char selectedLevel = 0;

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
    levelSelectText = LoadTexture("data/sprites/level_select.png");
    levelSelectCursor = LoadTexture("data/sprites/select_cursor.png");

    levelIcon1 = LoadTexture("data/sprites/stage1.png");
    levelIcon1G = LoadTexture("data/sprites/stage1g.png");
    levelIcon2 = LoadTexture("data/sprites/stage2.png");
    levelIcon2G = LoadTexture("data/sprites/stage2g.png");
    levelIcon3 = LoadTexture("data/sprites/stage3.png");
    levelIcon3G = LoadTexture("data/sprites/stage3g.png");
    levelIcon4 = LoadTexture("data/sprites/stage4.png");
    levelIcon4G = LoadTexture("data/sprites/stage4g.png");
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

char ProcessLevelSelect(){
    if (IsKeyPressed(CONTROL_UP)){
        selectCursorY = 1;
        PlaySFX(SFX_CURSOR);
    } else if (IsKeyPressed(CONTROL_DOWN)){
        selectCursorY = 0;
        PlaySFX(SFX_CURSOR);
    } else if (IsKeyPressed(CONTROL_LEFT)){
        if (selectCursorX > 0){
            selectCursorX--;
            PlaySFX(SFX_CURSOR);
        }
    } else if (IsKeyPressed(CONTROL_RIGHT)){
        if (selectCursorX < 2){
            selectCursorX++;
            PlaySFX(SFX_CURSOR);
        }
    } else if (IsKeyPressed(CONTROL_CANCEL)){
        // currentGameState = GAME_STATE_LEVEL;
        if (selectCursorY == 1 && levelBeat[0] && levelBeat[1] && levelBeat[2]){
            selectedLevel = 4;
            return 1;
        } else if (selectCursorY == 0){
            if (!levelBeat[selectCursorX]){
                selectedLevel = selectCursorX + 1;
                PlaySFX(SFX_CURSOR);
                return 1;
            }
            return 0;
        }
    } else if (IsKeyPressed(CONTROL_PAUSE)){
        currentGameState = GAME_STATE_MAIN_MENU;
        PlayBGM(BGM_MAIN);
    }
    return 0;
}

void DrawLevelSelect(){
    DrawTexture(levelSelectText, 7 * GAME_TILE_SIZE, GAME_TILE_SIZE, WHITE);
    if (levelBeat[0]){
        DrawTexture(levelIcon1G, 5 * GAME_TILE_SIZE, 8 * GAME_TILE_SIZE, WHITE);
    } else {
        DrawTexture(levelIcon1, 5 * GAME_TILE_SIZE, 8 * GAME_TILE_SIZE, WHITE);
    }

    if (levelBeat[1]){
        DrawTexture(levelIcon2G, 11 * GAME_TILE_SIZE, 8 * GAME_TILE_SIZE, WHITE);
    } else {
        DrawTexture(levelIcon2, 11 * GAME_TILE_SIZE, 8 * GAME_TILE_SIZE, WHITE);
    }

    if (levelBeat[2]){
        DrawTexture(levelIcon3G, 17 * GAME_TILE_SIZE, 8 * GAME_TILE_SIZE, WHITE);
    } else {
        DrawTexture(levelIcon3, 17 * GAME_TILE_SIZE, 8 * GAME_TILE_SIZE, WHITE);
    }
    if (levelBeat[0] & levelBeat[1] && levelBeat[2]){
        DrawTexture(levelIcon4, 11 * GAME_TILE_SIZE, 3 * GAME_TILE_SIZE, WHITE);
    } else {
        DrawTexture(levelIcon4G, 11 * GAME_TILE_SIZE, 3 * GAME_TILE_SIZE, WHITE);
    }
    if (selectCursorY == 1){
        DrawTexture(levelSelectCursor, 11 * GAME_TILE_SIZE, 3 * GAME_TILE_SIZE, WHITE);
    } else {
        DrawTexture(levelSelectCursor, (5 + (6 * selectCursorX)) * GAME_TILE_SIZE, 8 * GAME_TILE_SIZE, WHITE);
    }
}
