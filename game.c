#include "game.h"

Player *player;
MapData *testMap;
// Camera2D camera;

float deltaTime;

Level *currentLevel;

// Init the Game
void GameInit(){
    G_PlayerProjCount = 0;
    player = LoadPlayer(17 * GAME_TILE_SIZE, 10 * GAME_TILE_SIZE);

    testMap = LoadMapDataFromFile("./data/mapdata/map1.emp");
    SetMapTileSet("./data/tilesets/map1.png", testMap, 48);

    LoadProjectileTextures();
    LoadEnemyTextures();

    currentLevel = LoadLevel();

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

    AddEnemy(currentLevel, MakeEnemy(EN_WALK, (Vector2){20 * GAME_TILE_SIZE, 10 * GAME_TILE_SIZE}));
    Enemy *bossTrigger = MakeEnemy(EN_BOSSROOM_TRIGGER, (Vector2){17 * GAME_TILE_SIZE, 36 * GAME_TILE_SIZE});
    bossTrigger->respawnPosition = (Vector2){28.5 * GAME_TILE_SIZE, 33 * GAME_TILE_SIZE};
    bossTrigger->hitBox = (Rectangle){bossTrigger->position.x, bossTrigger->position.y, 23 * GAME_TILE_SIZE, 3 * GAME_TILE_SIZE};
    AddEnemy(currentLevel, bossTrigger);
    bossTrigger = NULL;
}

void GameLoop(){
    // Handle Events Down Here...
    
    // Unload Stuff that needs to be unloaded Down Here...
    CleanUpProjectile(currentLevel);
    // Process Logic Down Here...
    deltaTime = GetFrameTime();
    ProcessPlayer(player, testMap, currentLevel, deltaTime);
    ProcessLevelEnemy(currentLevel, testMap, deltaTime);
    ProcessLevelProjectile(currentLevel, testMap, deltaTime);
    if (currentLevel->camera->followPlayer){
        // currentLevel->camera->camera.target.x = player->position.x;
        // currentLevel->camera->camera.target.y = player->position.y;
        InterpolateCameraToPos(currentLevel->camera, player->position, 16.0, deltaTime);
    }
    // Draw Stuff Down Here...
    // Draw Worldspace Stuff
    BeginDrawing();
    ClearBackground(BLACK);
    BeginMode2D(currentLevel->camera->camera);
    // Draw Map
    for (int i = (((int)currentLevel->camera->camera.target.y - (int)currentLevel->camera->camera.offset.y) / GAME_TILE_SIZE); i < ((int)currentLevel->camera->camera.target.y + (int)currentLevel->camera->camera.offset.y) / 48 + 1; i++){
        for (int j = (((int)currentLevel->camera->camera.target.x - (int)currentLevel->camera->camera.offset.x) / GAME_TILE_SIZE); j < ((int)currentLevel->camera->camera.target.x + (int)currentLevel->camera->camera.offset.x) / 48 + 1; j++){
            if (i < testMap->height && i >= 0 && j < testMap->width && j >= 0){
                int offset = i * testMap->width + j;
                if (testMap->mapData[offset] > 0){
                    DrawTexture(*(testMap->tileSet->tileTextures + testMap->mapData[offset]), j * 48, i * 48, WHITE);
                }
            }
        }
    }
    DrawPlayer(player);
    DrawLevelEnemy(currentLevel);
    DrawLevelProjectile(currentLevel);
    EndMode2D();
    // Draw Screenspace Stuff
	DrawText("It works!", 20, 20, 20, WHITE);
    DrawFPS(1000, 100);
	DrawText(TextFormat("%f", deltaTime), 100, 100, 20, WHITE);
	EndDrawing();
}

// Clean Up All the Used Memory
void GameCleanUp(){
    UnloadPlayer(player);
    UnloadProjectileTextures();
    UnloadEnemyTextures();
    UnloadLevel(currentLevel);
    // UnloadMapData(testMap);
}