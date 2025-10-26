#include "level.h"

Level* LoadLevel(char id){
    Level *temp = (Level *)malloc(sizeof(Level));
    temp->levelId = id;
    for (int i = 0 ;i < sizeof(temp->projectiles) / sizeof(Projectile *); i++){
        temp->projectiles[i] = NULL;
    }
    for (int i = 0 ;i < sizeof(temp->enemies) / sizeof(Enemy *); i++){
        temp->enemies[i] = NULL;
    }
    temp->camera = malloc(sizeof(GameCamera));
    return temp; 
}

void UnloadLevel(Level *level){
    for (int i = 0 ;i < sizeof(level->projectiles) / sizeof(Projectile *); i++){
        if (level->projectiles[i] != NULL){
            UnloadProjectile(level->projectiles[i]);
            level->projectiles[i] = NULL;
        }
    }
    for (int i = 0 ;i < sizeof(level->enemies) / sizeof(Enemy *); i++){
        if (level->enemies[i] != NULL){
            UnloadEnemy(level->enemies[i]);
            level->enemies[i] = NULL;
        }
    }
    free(level->camera);
    free(level);
    level = NULL;
}

void AddProjectile(Level *level, Projectile *toAdd){
    for (int i = 0 ;i < sizeof(level->projectiles) / sizeof(Projectile *); i++){
        if (level->projectiles[i] == NULL){
            level->projectiles[i] = toAdd;
            break;
        }
    }
}

void ProcessLevelProjectile(Level *level, MapData *mapData, float deltaTime){
    for (int i = 0 ;i < sizeof(level->projectiles) / sizeof(Projectile *); i++){
        if (level->projectiles[i] != NULL){
            ProcessProjectile(level->projectiles[i], mapData, level, deltaTime);
        }
    }
}

void DrawLevelProjectile(Level *level){
    for (int i = 0 ;i < sizeof(level->projectiles) / sizeof(Projectile *); i++){
        if (level->projectiles[i] != NULL){
            DrawProjectile(level->projectiles[i]);
        }
    }
}

void CleanUpProjectile(Level *level){
    for (int i = 0 ;i < sizeof(level->projectiles) / sizeof(Projectile *); i++){
        if (level->projectiles[i] != NULL){
            if (level->projectiles[i]->toBeUnload){
                UnloadProjectile(level->projectiles[i]);
                level->projectiles[i] = NULL;
            }
        }
    }
}

void AddEnemy(Level *level, Enemy *toAdd){
    for (int i = 0 ;i < sizeof(level->enemies) / sizeof(Enemy *); i++){
        if (level->enemies[i] == NULL){
            level->enemies[i] = toAdd;
            break;
        }
    }
}

void ProcessLevelEnemy(Level *level, MapData *mapData, float deltaTime){
    for (int i = 0 ;i < sizeof(level->enemies) / sizeof(Enemy *); i++){
        if (level->enemies[i] != NULL){
            ProcessEnemy(level->enemies[i], mapData, level, deltaTime);
        }
    }
}

void DrawLevelEnemy(Level *level){
    for (int i = 0 ;i < sizeof(level->enemies) / sizeof(Enemy *); i++){
        if (level->enemies[i] != NULL){
            DrawEnemy(level->enemies[i]);
        }
    }
}

void CleanUpEnemy(Level *level){
    for (int i = 0 ;i < sizeof(level->enemies) / sizeof(Enemy *); i++){
        if (level->enemies[i] != NULL){
            if (level->enemies[i]->toBeUnload){
                UnloadEnemy(level->enemies[i]);
                level->enemies[i] = NULL;
            }
        }
    }
}