#include "pause_menu.h"

Texture pausePanel;
Texture pauseCursor;

Texture element1;
Texture element1G;

Texture element2;
Texture element2G;

Texture element3;
Texture element3G;

Texture element4;
Texture element4G;

Texture elementBar1;
Texture elementBarG;
Texture elementBar2;
Texture elementBar3;
Texture elementBar4;

char pauseCursorPos = 0;

void ResetPauseMenu(){
    pauseCursorPos = 0;
}
void LoadPauseMenu(){
    ResetPauseMenu();
    pausePanel = LoadTexture("data/sprites/skill_panel.png");
    pauseCursor = LoadTexture("data/sprites/skill_selector.png");

    element1 = LoadTexture("data/sprites/skill1.png");
    element1G = LoadTexture("data/sprites/skill1g.png");

    element2 = LoadTexture("data/sprites/skill2.png");
    element2G = LoadTexture("data/sprites/skill2g.png");

    element3 = LoadTexture("data/sprites/skill3.png");
    element3G = LoadTexture("data/sprites/skill3g.png");

    element4 = LoadTexture("data/sprites/skill4.png");
    element4G = LoadTexture("data/sprites/skill4g.png");

    elementBar1 = LoadTexture("data/sprites/normal_bar.png");
    elementBarG = LoadTexture("data/sprites/grey_bar.png");
    elementBar2 = LoadTexture("data/sprites/electric_bar.png");
    elementBar3 = LoadTexture("data/sprites/earth_bar.png");
    elementBar4 = LoadTexture("data/sprites/water_bar.png");
}

void UnloadPauseMenu(){
    UnloadTexture(pausePanel);
    UnloadTexture(pauseCursor);
    UnloadTexture(element1);
    UnloadTexture(element1G);
    UnloadTexture(element2);
    UnloadTexture(element2G);
    UnloadTexture(element3);
    UnloadTexture(element3G);
    UnloadTexture(element4);
    UnloadTexture(element4G);

    UnloadTexture(elementBar1);
    UnloadTexture(elementBarG);
    UnloadTexture(elementBar2);
    UnloadTexture(elementBar3);
    UnloadTexture(elementBar4);
}

void ProcessPauseMeun(Player* player){
    if (IsKeyPressed(CONTROL_UP)){
        if (pauseCursorPos > 0){
            pauseCursorPos--;
            PlaySFX(SFX_CURSOR);
        }
    } else if (IsKeyPressed(CONTROL_DOWN)){
        if (pauseCursorPos < 3){
            pauseCursorPos++;
            PlaySFX(SFX_CURSOR);
        }
    } else if (IsKeyPressed(CONTROL_PAUSE)){
        if (levelBeat[pauseCursorPos - 1] || pauseCursorPos == 0){
            switch (pauseCursorPos)
            {
            case 0:
                player->element = EL_NORMAL;
                break;
            case 1:
                player->element = EL_ELECTRIC;
                break;
            case 2:
                player->element = EL_EARTH;
                break;
            case 3:
                player->element = EL_WATER;
                break;
            }
            currentGameState = GAME_STATE_LEVEL;
            PlaySFX(SFX_CURSOR);
        } else {
            PlaySFX(SFX_ATTACK);
        }
    }
}

void DrawPauseMenu(Player* player){
    DrawTexture(pausePanel, 16 * GAME_TILE_SIZE, 1 * GAME_TILE_SIZE, WHITE);

    DrawTexture(element1, 17 * GAME_TILE_SIZE, 2 * GAME_TILE_SIZE, WHITE);
    if (levelBeat[0]){
        DrawTexture(element2, 17 * GAME_TILE_SIZE, 4 * GAME_TILE_SIZE, WHITE);
    } else {
        DrawTexture(element2G, 17 * GAME_TILE_SIZE, 4 * GAME_TILE_SIZE, WHITE);
    }
    if (levelBeat[1]){
        DrawTexture(element3, 17 * GAME_TILE_SIZE, 6 * GAME_TILE_SIZE, WHITE);
    } else {
        DrawTexture(element3G, 17 * GAME_TILE_SIZE, 6 * GAME_TILE_SIZE, WHITE); 
    }
    if (levelBeat[2]){
        DrawTexture(element4, 17 * GAME_TILE_SIZE, 8 * GAME_TILE_SIZE, WHITE);
    } else {
        DrawTexture(element4G, 17 * GAME_TILE_SIZE, 8 * GAME_TILE_SIZE, WHITE);
    }

    DrawTextureRec(elementBar1, (Rectangle){0, 0, player->hp * 18, 48}, (Vector2){19 * GAME_TILE_SIZE, 2 * GAME_TILE_SIZE}, WHITE);
    if (levelBeat[0]){
        DrawTextureRec(elementBar2, (Rectangle){0, 0, (player->elPower1 / 8) * 18, 48}, (Vector2){19 * GAME_TILE_SIZE, 4 * GAME_TILE_SIZE}, WHITE);
    } else {
        DrawTexture(elementBarG, 19 * GAME_TILE_SIZE, 4 * GAME_TILE_SIZE, WHITE);
    }
    if (levelBeat[1]){
        DrawTextureRec(elementBar3, (Rectangle){0, 0, (player->elPower2 / 8) * 18, 48}, (Vector2){19 * GAME_TILE_SIZE, 6 * GAME_TILE_SIZE}, WHITE);
    } else {
        DrawTexture(elementBarG, 19 * GAME_TILE_SIZE, 6 * GAME_TILE_SIZE, WHITE);
    }
    if (levelBeat[2]){
        DrawTextureRec(elementBar4, (Rectangle){0, 0, (player->elPower3 / 8) * 18, 48}, (Vector2){19 * GAME_TILE_SIZE, 8 * GAME_TILE_SIZE}, WHITE);
    } else {
        DrawTexture(elementBarG, 19 * GAME_TILE_SIZE, 8 * GAME_TILE_SIZE, WHITE);
    }
    
    DrawTexture(pauseCursor, 17 * GAME_TILE_SIZE, (2 + (2 * pauseCursorPos)) * GAME_TILE_SIZE, WHITE);
}