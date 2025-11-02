#include "game.h"

Player *player = NULL;
MapData *currentMap = NULL;
// Camera2D camera;

Texture2D dummyText33; // fix memory bug for some reason...

Texture2D playerHpBar;
Texture2D playerElBar1;
Texture2D playerElBar2;
Texture2D playerElBar3;

Texture2D dummyText34; // fix memory bug for some reason...

float deltaTime;

Level *currentLevel = NULL;

// Init the Game
void GameInit(){
    SetExitKey(KEY_NULL);

    scrollTexture[0] = LoadTexture("data/sprites/scroll_bg/scroll_bg1.png");
    scrollTexture[1] = LoadTexture("data/sprites/scroll_bg/scroll_bg2.png");
    scrollTexture[2] = LoadTexture("data/sprites/scroll_bg/scroll_bg3.png");
    scrollTexture[3] = LoadTexture("data/sprites/scroll_bg/scroll_bg4.png");
    scrollTexture[4] = LoadTexture("data/sprites/scroll_bg/scroll_bg5.png");
    scrollTexture[5] = LoadTexture("data/sprites/scroll_bg/scroll_bg6.png");
    scrollTexture[6] = LoadTexture("data/sprites/scroll_bg/scroll_bg7.png");
    scrollTexture[7] = LoadTexture("data/sprites/scroll_bg/scroll_bg8.png");
    scrollTexture[8] = LoadTexture("data/sprites/scroll_bg/scroll_bg9.png");
    scrollTexture[9] = LoadTexture("data/sprites/scroll_bg/scroll_bg10.png");
    scrollTexture[10] = LoadTexture("data/sprites/scroll_bg/scroll_bg11.png");
    scrollTexture[11] = LoadTexture("data/sprites/scroll_bg/scroll_bg12.png");
    scrollTexture[12] = LoadTexture("data/sprites/scroll_bg/scroll_bg13.png");
    scrollTexture[13] = LoadTexture("data/sprites/scroll_bg/scroll_bg14.png");
    scrollTexture[14] = LoadTexture("data/sprites/scroll_bg/scroll_bg15.png");
    scrollTexture[15] = LoadTexture("data/sprites/scroll_bg/scroll_bg16.png");

    bgSolid = LoadTexture("data/sprites/bg_solid.png");

    LoadAudio();
    LoadMainMenu();
    LoadLevelSelect();
    LoadWinScreen();
    LoadPasswordSelect();
    LoadPauseMenu();
    LoadEndScreen();

    SetRandomSeed(451); // Yes, this is intentional...

    // G_PlayerProjCount = 0;
    // player = LoadPlayer(17 * GAME_TILE_SIZE, 12 * GAME_TILE_SIZE);

    // currentMap = LoadMapDataFromFile("data/mapdata/map1.emp");
    // SetMapTileSet("data/tilesets/map1.png", currentMap, 48);

    LoadProjectileTextures();
    LoadEnemyTextures();

    playerHpBar = LoadTexture("data/sprites/normal_bar.png");
    

    // currentLevel = LoadLevel();

    // currentLevel->camera->camera.target.x += 144;
    // currentLevel->camera->camera.target.y += 144;

    // currentLevel->camera->camera = (Camera2D){0};
    // currentLevel->camera->camera.target = (Vector2){SCREEN_WIDTH / 2.0, SCREEN_HEIGHT / 2.0};
    // currentLevel->camera->camera.offset = (Vector2){SCREEN_WIDTH / 2.0, SCREEN_HEIGHT / 2.0};
    // currentLevel->camera->camera.rotation = 0.0;
    // currentLevel->camera->camera.zoom = 1.0;

    // currentLevel->player = player;

    // currentLevel->camera->camera.target = player->position;
    // currentLevel->camera->followPlayer = 1;

    // AddEnemy(currentLevel, MakeEnemy(EN_WALK, (Vector2){20 * GAME_TILE_SIZE, 10 * GAME_TILE_SIZE}));

    PlayBGM(BGM_MAIN);
}

void InitSelectedLevel(char selected){

    if (player != NULL){
        UnloadPlayer(player);
    }
    if (currentLevel != NULL){
        UnloadLevel(currentLevel);
    }
    if (currentMap != NULL){
        UnloadMapData(currentMap);
    }

    G_PlayerProjCount = 0;
    player = LoadPlayer(17 * GAME_TILE_SIZE, 12 * GAME_TILE_SIZE);
    
    currentLevel = LoadLevel(selected);

    currentLevel->camera->camera.target.x += 144;
    currentLevel->camera->camera.target.y += 144;

    currentLevel->camera->camera = (Camera2D){0};
    currentLevel->camera->camera.target = (Vector2){SCREEN_WIDTH / 2.0, SCREEN_HEIGHT / 2.0};
    currentLevel->camera->camera.offset = (Vector2){SCREEN_WIDTH / 2.0, SCREEN_HEIGHT / 2.0};
    currentLevel->camera->camera.rotation = 0.0;
    currentLevel->camera->camera.zoom = 1.0;

    currentLevel->player = player;

    currentLevel->camera->camera.target = player->position;
    currentLevel->camera->followPlayer = 1;

    Enemy *bossTrigger = MakeEnemy(EN_BOSSROOM_TRIGGER, (Vector2){17 * GAME_TILE_SIZE, 36 * GAME_TILE_SIZE});
    bossTrigger->respawnPosition = (Vector2){29 * GAME_TILE_SIZE, 33 * GAME_TILE_SIZE};
    bossTrigger->hitBox = (Rectangle){bossTrigger->position.x, bossTrigger->position.y, 23 * GAME_TILE_SIZE, 3 * GAME_TILE_SIZE};
    AddEnemy(currentLevel, bossTrigger);
    bossTrigger = NULL;

    switch (selected){
    case 1:
        currentMap = LoadMapDataFromFile("data/mapdata/map2.emp");
        SetMapTileSet("data/tilesets/map1.png", currentMap, 48);

        AddEnemy(currentLevel, MakeEnemy(EN_BOSS1, (Vector2){35 * GAME_TILE_SIZE, 37 * GAME_TILE_SIZE}));
        break;
    case 2:
        currentMap = LoadMapDataFromFile("data/mapdata/map2.emp");
        SetMapTileSet("data/tilesets/map2.png", currentMap, 48);

        AddEnemy(currentLevel, MakeEnemy(EN_BOSS2, (Vector2){35 * GAME_TILE_SIZE, 37 * GAME_TILE_SIZE}));
        break;
    case 3:
        currentMap = LoadMapDataFromFile("data/mapdata/map2.emp");
        SetMapTileSet("data/tilesets/map3.png", currentMap, 48);

        AddEnemy(currentLevel, MakeEnemy(EN_BOSS3, (Vector2){35 * GAME_TILE_SIZE, 37 * GAME_TILE_SIZE}));
        break;
    case 4:
        currentMap = LoadMapDataFromFile("data/mapdata/map2.emp");
        SetMapTileSet("data/tilesets/map4.png", currentMap, 48);

        AddEnemy(currentLevel, MakeEnemy(EN_BOSS4, (Vector2){35 * GAME_TILE_SIZE, 36 * GAME_TILE_SIZE}));
        break;
    }

    currentGameState = GAME_STATE_LEVEL;
}

void GameLoop(){
    // Handle Events Down Here...
    // Process Logic Down Here...
    ProcessAudioUpdate();
    deltaTime = GetFrameTime();
    switch (currentGameState)
    {
        case GAME_STATE_MAIN_MENU:
            ProcessMainMenu(deltaTime);
            break;
        case GAME_STATE_LEVEL_SELECT:
            if(ProcessLevelSelect(deltaTime)){
                InitSelectedLevel(selectedLevel);
            }
            break;
        case GAME_STATE_PASSWORD:
            ProcessPasswordSelect(deltaTime);
            break;
        case GAME_STATE_LEVEL:
            // Unload Stuff that needs to be unloaded Down Here...
            CleanUpProjectile(currentLevel);
            // Check For Pause Here
            if (IsKeyPressed(CONTROL_PAUSE)){
                currentGameState = GAME_STATE_PAUSED;
                break;
            }

            ProcessPlayer(player, currentMap, currentLevel, deltaTime);
            ProcessLevelEnemy(currentLevel, currentMap, deltaTime);
            ProcessLevelProjectile(currentLevel, currentMap, deltaTime);
            if (currentLevel->camera->followPlayer){
                // currentLevel->camera->camera.target.x = player->position.x;
                // currentLevel->camera->camera.target.y = player->position.y;
                InterpolateCameraToPos(currentLevel->camera, (Vector2){player->position.x + 36, player->position.y + 36}, 16.0, deltaTime);
            }
            break;
        case GAME_STATE_PAUSED:
            ProcessPauseMeun(player);
            break;
        case GAME_STATE_WIN:
            ProcessWinScreen(deltaTime);
            break;
        case GAME_STATE_WIN_END:
            ProcessEndScreen(deltaTime);
            break;

    }
    
    // Draw Stuff Down Here...
    BeginDrawing();
    ClearBackground(BLACK);
    switch (currentGameState)
    {
        case GAME_STATE_MAIN_MENU:
            DrawMainMeun();
            break;
        case GAME_STATE_LEVEL_SELECT:
            DrawLevelSelect();
            break;
        case GAME_STATE_PASSWORD:
            DrawPasswordSelect();
            break;
        case GAME_STATE_LEVEL:
            BeginMode2D(currentLevel->camera->camera);
            DrawMap(currentMap);
            DrawPlayer(player);
            DrawLevelEnemy(currentLevel);
            DrawLevelProjectile(currentLevel);
            EndMode2D();
            // Draw Screenspace Stuff (UI)
            DrawTextureRec(playerHpBar, (Rectangle){0, 0, player->hp * 18, 48}, (Vector2){GAME_TILE_SIZE, GAME_TILE_SIZE}, WHITE);
            switch (player->element)
            {
                case EL_ELECTRIC:
                    DrawTextureRec(elementBar2, (Rectangle){0, 0, (player->elPower1 / 8) * 18, 48}, (Vector2){GAME_TILE_SIZE, 3 * GAME_TILE_SIZE}, WHITE);
                    break;
                case EL_EARTH:
                    DrawTextureRec(elementBar3, (Rectangle){0, 0, (player->elPower2 / 8) * 18, 48}, (Vector2){GAME_TILE_SIZE, 3 * GAME_TILE_SIZE}, WHITE);
                    break;
                case EL_WATER:
                    DrawTextureRec(elementBar4, (Rectangle){0, 0, (player->elPower3 / 8) * 18, 48}, (Vector2){GAME_TILE_SIZE, 3 * GAME_TILE_SIZE}, WHITE);
                    break;
            }
            // DrawText("It works!", 20, 20, 20, WHITE);
            // DrawFPS(1000, 100);
            // DrawText(TextFormat("%f", deltaTime), 100, 100, 20, WHITE);
            break;
        case GAME_STATE_PAUSED:
            BeginMode2D(currentLevel->camera->camera);
            DrawMap(currentMap);
            DrawPlayer(player);
            DrawLevelEnemy(currentLevel);
            DrawLevelProjectile(currentLevel);
            EndMode2D();
            // Draw Screenspace Stuff (UI)
            DrawTextureRec(playerHpBar, (Rectangle){0, 0, player->hp * 18, 48}, (Vector2){GAME_TILE_SIZE, GAME_TILE_SIZE}, WHITE);
            // Pause menu sit of top of everything else
            DrawPauseMenu(player);
            break;
        case GAME_STATE_WIN:
            DrawWinScreen();
            break;
        case GAME_STATE_WIN_END:
            DrawEndScreen();
            break;
    }
    // Draw Worldspace Stuff
    EndDrawing();
    
}

// Clean Up All the Used Memory
void GameCleanUp(){
    UnloadTexture(scrollTexture[0]);
    UnloadTexture(scrollTexture[1]);
    UnloadTexture(scrollTexture[2]);
    UnloadTexture(scrollTexture[3]);
    UnloadTexture(scrollTexture[4]);
    UnloadTexture(scrollTexture[5]);
    UnloadTexture(scrollTexture[6]);
    UnloadTexture(scrollTexture[7]);
    UnloadTexture(scrollTexture[8]);
    UnloadTexture(scrollTexture[9]);
    UnloadTexture(scrollTexture[10]);
    UnloadTexture(scrollTexture[11]);
    UnloadTexture(scrollTexture[12]);
    UnloadTexture(scrollTexture[13]);
    UnloadTexture(scrollTexture[14]);
    UnloadTexture(scrollTexture[15]);

    UnloadTexture(bgSolid);
    UnloadMainMenu();
    UnloadLevelSelect();
    
    UnloadProjectileTextures();
    UnloadEnemyTextures();
    UnloadTexture(playerHpBar);

    if (player != NULL){
        UnloadPlayer(player);
    }
    if (currentLevel != NULL){
        UnloadLevel(currentLevel);
    }

    UnloadAudio();
    UnloadWinScreen();
    UnloadPasswordSelect();
    UnloadPauseMenu();
    UnloadEndScreen();
    // UnloadMapData(currentMap);
}