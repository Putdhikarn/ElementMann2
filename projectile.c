#include "projectile.h"

Texture projectileTextures[MAX_PROJECTILE_TYPE];

void LoadProjectileTextures(){
    projectileTextures[PROJ_PLAYER_NORMAL] = LoadTexture("data/sprites/player_projectile0.png");
    projectileTextures[PROJ_BOSS1] = LoadTexture("data/sprites/boss_projectile1.png");
    projectileTextures[PROJ_BOSS1_2] = LoadTexture("data/sprites/boss_projectile2.png");
    projectileTextures[PROJ_BOSS2] = LoadTexture("data/sprites/boss2_projectile.png");
}

// PROJ_PLAYER_NORMAL
void P0(Projectile *projectile, MapData *currentMap, Level *level, float deltaTime){
    projectile->position.x += projectile->velocity.x * deltaTime;
    projectile->position.y += projectile->velocity.y * deltaTime;
    projectile->hitBox.x = projectile->position.x + projectile->hitBoxOffset.x;
    projectile->hitBox.y = projectile->position.y + projectile->hitBoxOffset.y;

    Vector2 screenPos = GetWorldToScreen2D(projectile->position, level->camera->camera);
    // Check collision with enemy
    for (int i = 0; i < sizeof(level->enemies) / sizeof(Enemy*);i++){
        if (level->enemies[i] != NULL){
            if (CheckCollisionRecs(projectile->hitBox, level->enemies[i]->hitBox)){
                if (!level->enemies[i]->dead && level->enemies[i]->active && !projectile->hitSomething){
                    projectile->hitSomething = 1;
                    projectile->toBeUnload = 1;
                    DoEnemyHit(level->enemies[i], projectile->position, 0);
                }
            }
        }
    }
    // Unload projectile if offscreen
    if (screenPos.x < -projectile->spriteSize || screenPos.x > SCREEN_WIDTH + projectile->spriteSize || screenPos.y < -projectile->spriteSize || screenPos.y > SCREEN_HEIGHT + projectile->spriteSize){
        projectile->toBeUnload = 1;
    }
    
    projectile->spriteY = projectile->facing;
}

void D0(Projectile *projectile){
    DrawTextureRec(projectileTextures[projectile->type], (Rectangle){projectile->spriteX * projectile->spriteSize, projectile->spriteY * projectile->spriteSize, projectile->spriteSize, projectile->spriteSize}, projectile->position, WHITE);
}

//PROJ_BOSS1
void P1(Projectile *projectile, MapData *currentMap, Level *level, float deltaTime){
    projectile->position.x += projectile->velocity.x * deltaTime;
    projectile->position.y += projectile->velocity.y * deltaTime;
    projectile->hitBox.x = projectile->position.x + projectile->hitBoxOffset.x;
    projectile->hitBox.y = projectile->position.y + projectile->hitBoxOffset.y;

    Vector2 screenPos = GetWorldToScreen2D(projectile->position, level->camera->camera);
    // Check collision with player

    if (level->player != NULL){
        if (CheckCollisionRecs(projectile->hitBox, level->player->hitBox)){
            if (!projectile->hitSomething && !level->player->invincible && level->player->alive){
                projectile->hitSomething = 1;
                projectile->toBeUnload = 1;
                DoPlayerHit(level->player, (Vector2){projectile->hitBox.x + projectile->hitBox.width / 2, projectile->hitBox.y + projectile->hitBox.height / 2});
            }
        }
    }

    // Unload projectile if offscreen
    if (screenPos.x < -projectile->spriteSize || screenPos.x > SCREEN_WIDTH + projectile->spriteSize || screenPos.y < -projectile->spriteSize || screenPos.y > SCREEN_HEIGHT + projectile->spriteSize){
        projectile->toBeUnload = 1;
    }
    
    projectile->spriteY = projectile->facing;
}

//PROJ_BOSS1_2
void P2(Projectile *projectile, MapData *currentMap, Level *level, float deltaTime){
    projectile->position.x += projectile->velocity.x * deltaTime;
    projectile->position.y += projectile->velocity.y * deltaTime;
    projectile->hitBox.x = projectile->position.x + projectile->hitBoxOffset.x;
    projectile->hitBox.y = projectile->position.y + projectile->hitBoxOffset.y;

    Vector2 screenPos = GetWorldToScreen2D(projectile->position, level->camera->camera);
    // Check collision with player

    if (level->player != NULL){
        if (CheckCollisionRecs(projectile->hitBox, level->player->hitBox)){
            if (!projectile->hitSomething && !level->player->invincible && level->player->alive){
                projectile->hitSomething = 1;
                projectile->toBeUnload = 1;
                DoPlayerHit(level->player, (Vector2){projectile->hitBox.x + projectile->hitBox.width / 2, projectile->hitBox.y + projectile->hitBox.height / 2});
            }
        }
    }

    // Unload projectile if offscreen
    if (screenPos.x < -projectile->spriteSize || screenPos.x > SCREEN_WIDTH + projectile->spriteSize || screenPos.y < -projectile->spriteSize || screenPos.y > SCREEN_HEIGHT + projectile->spriteSize){
        projectile->toBeUnload = 1;
    }
}



Projectile* MakeProjectile(PROJ_TYPE type, Vector2 pos, Vector2 velocity, Vector2 hitBoxSize, Vector2 hitBoxOffset, int facing){
    Projectile *temp = (Projectile *)malloc(sizeof(Projectile));

    temp->toBeUnload = 0;

    temp->type = type;
    temp->position = pos;
    temp->velocity = velocity;

    temp->hitBoxOffset = hitBoxOffset;
    temp->hitBox = (Rectangle){temp->position.x + hitBoxOffset.x, temp->position.y + hitBoxOffset.y, hitBoxSize.x, hitBoxSize.y};

    temp->spriteTimer = 0.0;
    temp->facing = facing;
    temp->spriteX = 0;
    temp->spriteY = 0;

    temp->hitSomething = 0;
    temp->iSpeical = 0;
    temp->dSpecial = 0.0;

    switch (type){
        default:
            temp->spriteSize = 72;
            break;
        // case PROJ_PLAYER_NORMAL:
        //     temp->spriteSize = 72;
        //     break;
        // case PROJ_BOSS1:
        //     temp->spriteSize = 72;
        //     break;
        // case PROJ_BOSS1_2:
        //     temp->spriteSize = 72;
        //     break;
        // case PROJ_BOSS2:
        //     temp->spriteSize = 72;
        //     break;
    }

    return temp;
}

void ProcessProjectile(Projectile *projectile, MapData *currentMap, Level *level, float deltaTime){
    switch (projectile->type){
        case PROJ_PLAYER_NORMAL:
            P0(projectile, currentMap, level, deltaTime);
            break;
        case PROJ_BOSS1:
            P1(projectile, currentMap, level, deltaTime);
            break;
        case PROJ_BOSS1_2:
            P2(projectile, currentMap, level, deltaTime);
            break;
        case PROJ_BOSS2:
            P2(projectile, currentMap, level, deltaTime);
            break;
    }
}

void DrawProjectile(Projectile *projectile){
    switch (projectile->type){
        default :
            D0(projectile);
            break;
    }
}

void UnloadProjectile(Projectile *projectile){
    if (projectile){
        if (projectile->type == 0){
            G_PlayerProjCount--;
        }
        free(projectile);
    }
}

void UnloadProjectileTextures(){
    for (int i = 0; i < MAX_PROJECTILE_TYPE; i++){
        UnloadTexture(projectileTextures[i]);
    }
}

