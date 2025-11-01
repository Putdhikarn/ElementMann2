#include "end_screen.h"

Texture2D endBg;
Texture2D endElementMann;
Texture2D endGameby;
Texture2D endStudioName;
Texture2D endCredit;
Texture2D endNames;
Texture2D endThanks;

short endProgress = -1;
short endFade = 0;
char endFadeDir = 0;
double endTimer = 0;

void LoadEndScreen(){
    endBg = LoadTexture("data/sprites/endbg.png");
    endElementMann = LoadTexture("data/sprites/element_mann2.png");
    endGameby = LoadTexture("data/sprites/game_by.png");
    endStudioName = LoadTexture("data/sprites/gamedev.png");
    endCredit = LoadTexture("data/sprites/credits.png");
    endNames = LoadTexture("data/sprites/name2.png");
    endThanks = LoadTexture("data/sprites/the_end.png");
}

void UnloadEndScreen(){
    UnloadTexture(endBg);
    UnloadTexture(endElementMann);
    UnloadTexture(endGameby);
    UnloadTexture(endStudioName);
    UnloadTexture(endCredit);
    UnloadTexture(endNames);
    UnloadTexture(endThanks);
}
char ProcessEndScreen(double delta){
    endTimer += delta;
    if (endTimer >= 10.0){
        endTimer = 10.0;
    }
    if (endProgress >= 0 && endProgress < 3){
        if (endFadeDir){
            if (endFade <= 0){
                if (endTimer >= 0.2){
                    endFadeDir = 0;
                    endTimer = 0;
                    endProgress++;
                }
            } else {
                if (endTimer >= 1/30){
                    if (endProgress == 2){
                        endProgress = 3;
                    }
                    endFade--;
                    endTimer = 0;
                }
            }
        } else {
            if (endFade > 254){
                if (endTimer >= 5.0){
                    endFadeDir = 1;
                    endTimer = 0;
                }
            } else {
                if (endTimer >= 1/30){
                    endFade++;
                    endTimer = 0;
                }
            }
        }
    } else {
        if (endTimer >= 0.5){
            endTimer = 0;
            endProgress = 0;
        }
    }
    
}

void DrawEndScreen(){
    DrawTexture(endBg, 0, 0, WHITE);
    switch (endProgress){
    case 0:
        DrawTexture(endElementMann, 2 * GAME_TILE_SIZE, 2 * GAME_TILE_SIZE, (Color){255, 255, 255, endFade});
        DrawTexture(endGameby, 4 * GAME_TILE_SIZE, 4 * GAME_TILE_SIZE, (Color){255, 255, 255, endFade});
        DrawTexture(endStudioName, 2 * GAME_TILE_SIZE, 6 * GAME_TILE_SIZE, (Color){255, 255, 255, endFade});
        break;
    case 1:
        DrawTexture(endCredit, 2 * GAME_TILE_SIZE, 2 * GAME_TILE_SIZE, (Color){255, 255, 255, endFade});
        DrawTexture(endNames, 4 * GAME_TILE_SIZE, 4 * GAME_TILE_SIZE, (Color){255, 255, 255, endFade});
        break;
    default:
        DrawTexture(endThanks, 2 * GAME_TILE_SIZE, 5 * GAME_TILE_SIZE, (Color){255, 255, 255, endFade});
        break;
    }
}