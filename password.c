#include "password.h"

Texture panel;
Texture passwrodCursor;
Texture passwordReady;
Texture passwordDot;
Texture numText;
Texture dummyText2;

char passwordField[5][5] = {
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0}
};

char passwordDotLeft = 6;
char passwordCursorX = 0;
char passwordCursorY = 0;
char passwordValid = 0;

void LoadPasswordSelect(){
    panel = LoadTexture("data/sprites/password_panel.png");
    passwrodCursor = LoadTexture("data/sprites/password_cursor2.png");
    passwordReady = LoadTexture("data/sprites/password_start.png");
    passwordDot = LoadTexture("data/sprites/password_dot.png");
    numText = LoadTexture("data/sprites/password_nums.png");
}

void UnloadPasswordSelect(){
    UnloadTexture(panel);
    UnloadTexture(passwrodCursor);
    UnloadTexture(passwordReady);
    UnloadTexture(passwordDot);
    UnloadTexture(numText);
}

void ProcessPasswordSelect(double delta){
    // bg scroll
    if (scrollTime >= 1.0/120.0){
        scrollTime = 0;
        if (scrollFrame >= 16){
            scrollFrame = 0;
        } else {
            scrollFrame ++;
        }
    } else {
        scrollTime += delta;
    }

    passwordValid = 0;
    if (passwordField[4][0] && passwordField[1][1]){
        passwordValid = 1;
    }
    if (passwordField[3][0] && passwordField[4][3]){
        passwordValid = 1;
    }
    if (passwordField[3][4] && passwordField[2][2]){
        passwordValid = 1;
    }

    if (IsKeyPressed(CONTROL_UP)){
        if (passwordCursorY > 0){
            passwordCursorY--;
            PlaySFX(SFX_CURSOR);
        }
    } else if (IsKeyPressed(CONTROL_DOWN)){
        if (passwordCursorY < 4){
            passwordCursorY++;
            PlaySFX(SFX_CURSOR);
        }
    } else if (IsKeyPressed(CONTROL_LEFT)){
        if (passwordCursorX > 0){
            passwordCursorX--;
            PlaySFX(SFX_CURSOR);
        }
    } else if (IsKeyPressed(CONTROL_RIGHT)){
        if (passwordCursorX < 4){
            passwordCursorX++;
            PlaySFX(SFX_CURSOR);
        }
    } else if (IsKeyPressed(CONTROL_CANCEL)){
        if (passwordField[passwordCursorY][passwordCursorX]){
            passwordField[passwordCursorY][passwordCursorX] = 0;
            passwordDotLeft++;
            PlaySFX(SFX_CURSOR);
        } else if (!passwordField[passwordCursorY][passwordCursorX] && passwordDotLeft > 0){
            passwordField[passwordCursorY][passwordCursorX] = 1;
            passwordDotLeft--;
            PlaySFX(SFX_CURSOR);
        }
    } else if (IsKeyPressed(CONTROL_CONFIRM)){
        if (passwordValid){
            if (passwordField[4][0] && passwordField[1][1]){
                levelBeat[0] = 1;
            }
            if (passwordField[3][0] && passwordField[4][3]){
                levelBeat[1] = 1;
            }
            if (passwordField[3][4] && passwordField[2][2]){
                levelBeat[2] = 1;
            }
            currentGameState = GAME_STATE_LEVEL_SELECT;
            PlaySFX(SFX_CURSOR);
            PlayBGM(BGM_SELECT);
        }
    } else if (IsKeyPressed(CONTROL_PAUSE)){
        currentGameState = GAME_STATE_MAIN_MENU;
        PlayBGM(BGM_MAIN);
    }
}

void DrawPasswordSelect(){
    if (passwordField[4][0] && passwordField[1][1]){
        DrawTexture(bgSolid, 0, 0, COLOR_LEVEL_1);
    }
    if (passwordField[3][0] && passwordField[4][3]){
        DrawTexture(bgSolid, 384, 0, COLOR_LEVEL_2);
    }
    if (passwordField[3][4] && passwordField[2][2]){
        DrawTexture(bgSolid, 768, 0, COLOR_LEVEL_3);
    }
    DrawTextureRec(scrollTexture, (Rectangle){1152 * scrollFrame, 0, 1152, 672},(Vector2){0, 0}, WHITE);
    DrawTexture(panel, 0, 0, WHITE);
    DrawTexture(passwrodCursor, (8 + passwordCursorX) * GAME_TILE_SIZE, (5 + passwordCursorY) * GAME_TILE_SIZE, WHITE);
    DrawTextureRec(numText, (Rectangle){passwordDotLeft * GAME_TILE_SIZE, 0, GAME_TILE_SIZE, GAME_TILE_SIZE}, (Vector2){17 * GAME_TILE_SIZE, 4 * GAME_TILE_SIZE}, WHITE);
    for (int i = 0; i < 5; i++){
        for (int j = 0; j < 5; j++){
            if (passwordField[i][j] == 1){
                DrawTexture(passwordDot, (8 + j) * GAME_TILE_SIZE, (5 + i) * GAME_TILE_SIZE, WHITE);
            }
        }
    }
    if (passwordValid){
        DrawTexture(passwordReady, 9 * GAME_TILE_SIZE, 10 * GAME_TILE_SIZE, WHITE);
    }
}

