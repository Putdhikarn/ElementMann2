#include "game_struct.h"

int G_PlayerProjCount = 0;
GAME_STATE currentGameState = GAME_STATE_MAIN_MENU;
char levelBeat[4] = {0, 0, 0, 0};
char lastLevel = 0;
Texture2D scrollTexture;
Texture2D bgSolid;
char scrollFrame = 0;
double scrollTime = 0;