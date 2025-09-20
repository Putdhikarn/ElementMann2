#include "game.h"

Player *player;
MapData *testMap;
Camera2D camera;

float deltaTime;

Level *currentLevel;

// Init the Game
void GameInit(){
    G_PlayerProjCount = 0;
    player = LoadPlayer(6 * 48, 8 * 48);

    camera = (Camera2D){0};
    camera.target = (Vector2){SCREEN_WIDTH / 2.0, SCREEN_HEIGHT / 2.0};
    camera.offset = (Vector2){SCREEN_WIDTH / 2.0, SCREEN_HEIGHT / 2.0};
    camera.rotation = 0.0;
    camera.zoom = 1.0;

    testMap = LoadMapDataFromFile("./data/mapdata/test.emp");
    SetMapTileSet("./data/tilesets/test.png", testMap, 48);

    LoadProjectileTextures();
    LoadEnemyTextures();

    camera.target.x += 144;
    camera.target.y += 144;

    currentLevel = LoadLevel(&camera);
    currentLevel->player = player;
    AddEnemy(currentLevel, MakeEnemy(EN_WALK, (Vector2){20 * GAME_TILE_SIZE, 10 * GAME_TILE_SIZE}));
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
    camera.target.x = player->position.x;
    // camera.target.y = player->position.y;
    // Draw Stuff Down Here...
    // Draw Worldspace Stuff
    BeginDrawing();
    ClearBackground(BLACK);
    BeginMode2D(camera);
    // Draw Map
    for (int i = (((int)camera.target.y - (int)camera.offset.y) / GAME_TILE_SIZE); i < ((int)camera.target.y + (int)camera.offset.y) / 48 + 1; i++){
        for (int j = (((int)camera.target.x - (int)camera.offset.x) / GAME_TILE_SIZE); j < ((int)camera.target.x + (int)camera.offset.x) / 48 + 1; j++){
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