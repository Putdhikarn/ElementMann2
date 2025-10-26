#include "enemy.h"
#include "game_struct.h"

#define ENEMY_INV_TIME_MAX 0.35 

Texture enemyTextures[MAX_ENEMY_TYPE];

void LoadEnemyTextures(){
    enemyTextures[EN_WALK] = LoadTexture("data/sprites/enemy.png");
    enemyTextures[EN_BOSS1] = LoadTexture("data/sprites/boss1.png");
    enemyTextures[EN_BOSS2] = LoadTexture("data/sprites/boss2.png");
    enemyTextures[EN_BOSS3] = LoadTexture("data/sprites/boss3.png");
    enemyTextures[EN_BOSS4] = LoadTexture("data/sprites/boss4.png");
}

Enemy* MakeEnemy(ENEMY_TYPE type, Vector2 pos){
    Enemy *temp = (Enemy *)malloc(sizeof(Enemy));

    temp->toBeUnload = 0;

    temp->type = type;
    temp->position = pos;
    temp->respawnPosition = pos;

    temp->spriteTimer = 0.0;
    temp->facing = 0;
    temp->spriteX = 0;
    temp->spriteXLast = 0;
    temp->spriteY = 0;

    temp->invincible = 0;
    temp->invTimer = 0;

    temp->respawnable = 1;
    temp->active = 0;
    temp->dead = 0;

    temp->cSpecial = 0;
    temp->iSpeical = 0;
    temp->iSpeical2 = 0;
    temp->dSpecial = 0.0;

    switch (type){
        case EN_WALK:
            temp->hitBoxOffset = (Vector2){12, 18};
            temp->hitBox = (Rectangle){temp->position.x + temp->hitBoxOffset.x, temp->position.y + temp->hitBoxOffset.y, 48, 51};
            temp->spriteSize = 72;
            temp->hp = 1;
            temp->respawnHp = temp->hp;
            temp->iSpeical = 1;
            temp->cSpecial2 = 0;
            break;
        case EN_BOSSROOM_TRIGGER:
            temp->hitBoxOffset = (Vector2){0, 0};
            temp->hitBox = (Rectangle){temp->position.x, temp->position.y, 1, 1};
            break;
        case EN_BOSS1:
            temp->hitBoxOffset = (Vector2){27, 21};
            temp->hitBox = (Rectangle){temp->position.x + temp->hitBoxOffset.x, temp->position.y + temp->hitBoxOffset.y, 48, 72};
            temp->spriteSize = 96;
            temp->hp = 24;
            temp->respawnHp = temp->hp;
            temp->cSpecial = 0;
            temp->iSpeical = 1;
            temp->iSpeical2 = 0;
            temp->dSpecial = 0;
            break;
        case EN_BOSS2:
            temp->hitBoxOffset = (Vector2){27, 21};
            temp->hitBox = (Rectangle){temp->position.x + temp->hitBoxOffset.x, temp->position.y + temp->hitBoxOffset.y, 48, 72};
            temp->spriteSize = 96;
            temp->hp = 24;
            temp->respawnHp = temp->hp;
            temp->cSpecial = 0;
            temp->iSpeical = 1;
            temp->iSpeical2 = 0;
            temp->dSpecial = 0;
            break;
        case EN_BOSS3:
            temp->hitBoxOffset = (Vector2){27, 21};
            temp->hitBox = (Rectangle){temp->position.x + temp->hitBoxOffset.x, temp->position.y + temp->hitBoxOffset.y, 48, 72};
            temp->spriteSize = 96;
            temp->hp = 24;
            temp->respawnHp = temp->hp;
            temp->cSpecial = 0;
            temp->iSpeical = 1;
            temp->iSpeical2 = 0;
            temp->dSpecial = 0;
            break;
        case EN_BOSS4:
            temp->hitBoxOffset = (Vector2){27, 21};
            temp->hitBox = (Rectangle){temp->position.x + temp->hitBoxOffset.x, temp->position.y + temp->hitBoxOffset.y, 48, 72};
            temp->spriteSize = 96;
            temp->hp = 56;
            temp->respawnHp = temp->hp;
            temp->cSpecial = 0;
            temp->iSpeical = 1;
            temp->iSpeical2 = 0;
            temp->dSpecial = 0;
            break;
    }

    return temp;
}

int IsRectOnScreen(Rectangle check, Camera2D camera){
    Rectangle screenRect = (Rectangle){camera.target.x - camera.offset.x, camera.target.y - camera.offset.y, SCREEN_WIDTH, SCREEN_HEIGHT};
    char tL = CheckCollisionPointRec((Vector2){check.x, check.y}, screenRect);
    char tR = CheckCollisionPointRec((Vector2){check.x + check.width, check.y}, screenRect);

    char bL = CheckCollisionPointRec((Vector2){check.x, check.y + check.height}, screenRect);
    char bR = CheckCollisionPointRec((Vector2){check.x + check.width, check.y + check.height}, screenRect);

    return (tL && tR && bL && bR);
}

int IsRectOnScreenPartial(Rectangle check, Camera2D camera){
    Rectangle screenRect = (Rectangle){camera.target.x - camera.offset.x, camera.target.y - camera.offset.y, SCREEN_WIDTH, SCREEN_HEIGHT};
    return CheckCollisionRecs(screenRect, check);
}

int checkEnemyOnGround(Enemy *enemy, MapData *currentMap){
    int botLeft = IsTileAtPositionBlocking(currentMap, enemy->hitBox.x, enemy->hitBox.y + enemy->hitBox.height + 2); 
    int botRight = IsTileAtPositionBlocking(currentMap, enemy->hitBox.x + enemy->hitBox.width, enemy->hitBox.y + enemy->hitBox.height + 2);

    return botRight || botLeft;
}

// Apply the Enemy Velocity to Enemy Position (And do some hitbox magics so the Enemy won't go though a tile)
void ApplyEnemyVelocity(Enemy *enemy, MapData *currentMap, float deltaTime){
    Vector2 applyVelocity = {enemy->velocity.x * deltaTime, enemy->velocity.y * deltaTime};

    // apply x
    // check if the Enemy will overlap the any-tile with the current velocity, 
    // modify the velocity so that the Enemy won't overlap and get stuck inside a tile
    if (IsRectAtPostitionIntersectAnyTile(currentMap, (Rectangle){enemy->hitBox.x + applyVelocity.x, enemy->hitBox.y, enemy->hitBox.width, enemy->hitBox.height})){
        applyVelocity.x = 0;
    }
    // apply y
    // check if the Enemy will overlap the any-tile with the current velocity, 
    // modify the velocity so that the Enemy won't overlap and get stuck inside a tile
    if (IsRectAtPostitionIntersectAnyTile(currentMap, (Rectangle){enemy->hitBox.x, enemy->hitBox.y + applyVelocity.y, enemy->hitBox.width, enemy->hitBox.height})) {
        if (applyVelocity.y > 0){
            applyVelocity.y = ((((int)(enemy->hitBox.y + enemy->hitBox.height + applyVelocity.y) / GAME_TILE_SIZE) * GAME_TILE_SIZE) - (enemy->hitBox.y + enemy->hitBox.height + 1));
            enemy->velocity.y = 0;
        } else {
            applyVelocity.y = ((((int)(enemy->hitBox.y + applyVelocity.y) / GAME_TILE_SIZE) * GAME_TILE_SIZE) + GAME_TILE_SIZE) - (enemy->hitBox.y - 1);
            enemy->velocity.y = 0;
        }
    }

    enemy->position.x += applyVelocity.x;
    enemy->position.y += applyVelocity.y;

    enemy->hitBox.x = enemy->position.x + enemy->hitBoxOffset.x;
    enemy->hitBox.y = enemy->position.y + enemy->hitBoxOffset.y;
}

void DoEnemyHit(Enemy *enemy, Vector2 hitPos, int elementType){
    if (enemy->invincible == 0){
        enemy->invincible = 1;
        enemy->invTimer = 0.0;
        enemy->hp--;
        if (enemy->hp <= 0){
            if (!enemy->respawnable){
                enemy->toBeUnload = 1;
            }
            enemy->dead = 1;
        }
    }
}

void DoEnemyInvCheck(Enemy *enemy, float deltaTime){
    if (enemy->invincible == 1){
        if (enemy->invTimer >= ENEMY_INV_TIME_MAX){
            enemy->invincible = 0;
        } else {
            enemy->invTimer += deltaTime;
        }
    }
}

void CheckCollisionWithPlayer(Enemy *enemy, Level *level){
    if (CheckCollisionRecs(enemy->hitBox, level->player->hitBox) && !level->player->invincible && level->player->alive){
        DoPlayerHit(level->player, (Vector2){enemy->hitBox.x + (enemy->hitBox.width / 2), enemy->hitBox.y});
    }
}

char GetEnemyFacingToPlayer(Enemy *enemy, Level *level){
    return (enemy->hitBox.x + enemy->hitBox.width / 2 < level->player->hitBox.x + level->player->hitBox.width / 2);
}

// Unused, Cause there no more time to make an actual level, only boss.
// Code left here for reference.
void EP0(Enemy *enemy, MapData *currentMap, Level *level, float deltaTime){
    // invincibility check
    DoEnemyInvCheck(enemy, deltaTime);
    // spawn/Respawn enemy when on screen
    if (IsRectOnScreen(enemy->hitBox, level->camera->camera) && !enemy->active && !enemy->dead){
        enemy->active = 1;
    } 
    // despawn when off screen
    else if ((!IsRectOnScreen(enemy->hitBox, level->camera->camera) && enemy->dead) || !IsRectOnScreenPartial(enemy->hitBox, level->camera->camera)){
        enemy->active = 0;
        enemy->dead = 0;
    } 
    // normal process
    else if (!enemy->dead && enemy->active){
        if (enemy->iSpeical && (!IsTileAtPositionBlocking(currentMap, enemy->hitBox.x - 2, enemy->hitBox.y + enemy->hitBox.height + 16) || 
            IsTileAtPositionBlocking(currentMap, enemy->hitBox.x - 4, enemy->hitBox.y + enemy->hitBox.height / 2.0))){
                enemy->iSpeical = 0;
        } else if (!enemy->iSpeical && (!IsTileAtPositionBlocking(currentMap, enemy->hitBox.x + enemy->hitBox.width + 2, enemy->hitBox.y + enemy->hitBox.height + 16) ||
            IsTileAtPositionBlocking(currentMap, enemy->hitBox.x + enemy->hitBox.width + 4, enemy->hitBox.y + enemy->hitBox.height / 2.0))){
                enemy->iSpeical = 1;
        }
        if (enemy->iSpeical){
            enemy->velocity.x = -60.0;
            enemy->facing = 0;
        } else {
            enemy->velocity.x = 60.0;
            enemy->facing = 1;
        }
        if (!checkEnemyOnGround(enemy, currentMap)){
            enemy->velocity.y = 120.0;
        } else {
            enemy->velocity.y = 0.0;
        }
        ApplyEnemyVelocity(enemy, currentMap, deltaTime);
        // animation stuff
        enemy->spriteY = enemy->facing;
        if (enemy->spriteTimer >= 0.14){
            enemy->spriteTimer = 0;
            if (enemy->spriteX == 0){
                enemy->spriteX = enemy->spriteXLast == 2 ? 1 : 2;
                enemy->spriteXLast = enemy->spriteX;
            } else {
                enemy->spriteX = 0;
            }
        } else {
            enemy->spriteTimer += deltaTime;
        }
        // Check collision with player
        CheckCollisionWithPlayer(enemy, level);
    }
    // reinit enemy for respawn
    else {
        enemy->iSpeical = enemy->respawnPosition.x > level->player->position.x;
        enemy->position = enemy->respawnPosition;
        enemy->velocity.x = 0;
        enemy->velocity.y = 0;
        enemy->invincible = 0;
        enemy->invTimer = 0.0;
        enemy->hp = enemy->respawnHp;
    }
}

void ED0(Enemy *enemy){
    if (!enemy->dead && enemy->active){
        DrawTextureRec(enemyTextures[enemy->type], (Rectangle){enemy->spriteX * enemy->spriteSize, enemy->spriteY * enemy->spriteSize, enemy->spriteSize, enemy->spriteSize}, enemy->position, WHITE);
    }
}

void ED02(Enemy *enemy){
    if (!enemy->dead && enemy->active){
        if (enemy->invincible){
            if (((int)(enemy->invTimer * 100000) % 2 == 0)){
                DrawTextureRec(enemyTextures[enemy->type], (Rectangle){enemy->spriteX * enemy->spriteSize, enemy->spriteY * enemy->spriteSize, enemy->spriteSize, enemy->spriteSize}, enemy->position, WHITE);
            }
        } else {
            DrawTextureRec(enemyTextures[enemy->type], (Rectangle){enemy->spriteX * enemy->spriteSize, enemy->spriteY * enemy->spriteSize, enemy->spriteSize, enemy->spriteSize}, enemy->position, WHITE);
        }
    }
}

void EP01(Enemy *enemy, MapData *currentMap, Level *level, float deltaTime){
    if (CheckCollisionRecs(enemy->hitBox, level->player->hitBox) && enemy->cSpecial == 0){
        level->camera->camera.target = enemy->respawnPosition;
        level->camera->followPlayer = 0;
        enemy->cSpecial = 1;
    } else if (!CheckCollisionRecs(enemy->hitBox, level->player->hitBox)){
        enemy->cSpecial = 0;
    }
}

void EP02(Enemy *enemy, MapData *currentMap, Level *level, float deltaTime){
    // change game state to win if boos is dead
    if (enemy->dead == 1 && enemy->type == EN_BOSS1) {
        currentGameState = GAME_STATE_WIN;
        return;
    }
    // invincibility check
    DoEnemyInvCheck(enemy, deltaTime);
    // spawn/Respawn enemy when on screen
    if (IsRectOnScreen(enemy->hitBox, level->camera->camera) && !enemy->active && !enemy->dead){
        enemy->active = 1;
    } 
    // despawn when off screen
    else if ((!IsRectOnScreen(enemy->hitBox, level->camera->camera) && enemy->dead) || !IsRectOnScreenPartial(enemy->hitBox, level->camera->camera)){
        enemy->active = 0;
        enemy->dead = 0;
    } 
    // normal process
    else if (!enemy->dead && enemy->active){
        int attackRng = GetRandomValue(0, 256);
        switch (enemy->cSpecial){
            // walking state
            case 0:
                if (enemy->iSpeical && (IsTileAtPositionBlocking(currentMap, enemy->hitBox.x - 8, enemy->hitBox.y + enemy->hitBox.height / 2.0))){
                        enemy->iSpeical = 0;
                        if ((float)enemy->hp / (float)enemy->respawnHp < 0.55 && attackRng % 2 == 0){
                            enemy->cSpecial = 2;
                            enemy->velocity.y = -1200;
                            ApplyEnemyVelocity(enemy, currentMap, deltaTime);
                            break;
                        } else {
                            enemy->cSpecial = 1;
                        }
                } else if (!enemy->iSpeical && (IsTileAtPositionBlocking(currentMap, enemy->hitBox.x + enemy->hitBox.width + 8, enemy->hitBox.y + enemy->hitBox.height / 2.0))){
                        enemy->iSpeical = 1;
                        if ((float)enemy->hp / (float)enemy->respawnHp < 0.55 && attackRng % 2 == 0){
                            enemy->cSpecial = 2;
                            enemy->velocity.y = -1200;
                            ApplyEnemyVelocity(enemy, currentMap, deltaTime);
                            break;
                        } else {
                            enemy->cSpecial = 1;
                        }
                }
                if (enemy->iSpeical){
                    enemy->velocity.x = -560.0;
                    enemy->facing = 0;
                } else {
                    enemy->velocity.x = 560.0;
                    enemy->facing = 1;
                }
                if (!checkEnemyOnGround(enemy, currentMap)){
                    enemy->velocity.y = 480.0;
                } else {
                    enemy->velocity.y = 0.0;
                }
                ApplyEnemyVelocity(enemy, currentMap, deltaTime);
                break;
            // shoot state
            case 1:
                if (enemy->dSpecial >= 0.35){
                    enemy->dSpecial = 0;
                    Vector2 pPos = enemy->facing == 0 ? (Vector2){enemy->position.x - 38, enemy->position.y + 32} : (Vector2){enemy->position.x + 46, enemy->position.y + 32};
                    Vector2 pVel = enemy->facing == 0 ? (Vector2){-1330.0, 0.0} : (Vector2){1330.0, 0.0};
                    AddProjectile(level, MakeProjectile(PROJ_BOSS1, pPos, pVel, (Vector2){24, 24}, (Vector2){21, 24}, enemy->facing));
                    enemy->iSpeical2++;
                    if (enemy->iSpeical2 >= 3){
                        enemy->iSpeical2 = 0;
                        if ((float)enemy->hp / (float)enemy->respawnHp < 0.55 && attackRng % 2 == 0){
                            enemy->cSpecial = 2;
                            enemy->velocity.y = -1200;
                            ApplyEnemyVelocity(enemy, currentMap, deltaTime);
                            break;
                        } else {
                            enemy->cSpecial = 0;
                        }
                    }
                } else {
                    enemy->dSpecial += deltaTime;
                }
                break;
            // jump to middle state
            case 2:
                if (enemy->iSpeical){
                    enemy->velocity.x = -560.0;
                    enemy->facing = 0;
                } else {
                    enemy->velocity.x = 560.0;
                    enemy->facing = 1;
                }
                if (!checkEnemyOnGround(enemy, currentMap)){
                    if (enemy->velocity.y < 0){
                        enemy->velocity.y += 2400.0 * deltaTime;
                    } else {
                        enemy->velocity.y += 3600.0 * deltaTime;
                    }
                } else {
                    enemy->cSpecial = 3;
                    enemy->spriteX = 0;
                    enemy->velocity.y = 0.0;
                }
                ApplyEnemyVelocity(enemy, currentMap, deltaTime);
                break;
            // shoot circle state
            case 3:
                if (enemy->dSpecial >= 0.25){
                    enemy->dSpecial = 0;
                    for (int i = 0; i <= 180; i += 36){
                        Vector2 pDir = (Vector2){cos((double)i * (PI / 180.0)), sin((double)i * (PI / 180.0))};
                        Vector2 pPos = (Vector2){enemy->hitBox.x + enemy->hitBox.width / 2, enemy->hitBox.y + enemy->hitBox.height / 2};
                        Vector2 pVel = (Vector2){1330.0, -1330.0};
                        pVel = Vector2Multiply(pVel, Vector2Normalize(pDir));
                        AddProjectile(level, MakeProjectile(PROJ_BOSS1_2, pPos, pVel, (Vector2){24, 24}, (Vector2){21, 24}, enemy->facing));
                        enemy->cSpecial = 0;
                    }
                } else {
                    enemy->dSpecial += deltaTime;
                }
                break;
        }
        // Check collision with player
        CheckCollisionWithPlayer(enemy, level);
        // animation stuff
        enemy->spriteY = enemy->facing;
        switch (enemy->cSpecial){
            case 0:
                 if (enemy->spriteTimer >= 0.1){
                    enemy->spriteTimer = 0;
                    if (enemy->spriteX == 4){
                        enemy->spriteX = 1;
                    } else {
                        enemy->spriteX++;
                    }
                } else {
                    enemy->spriteTimer += deltaTime;
                }
                break;
            case 1:
                enemy->spriteY += 2;
                enemy->spriteX = 0;
                break;
            case 2:
                enemy->spriteX = 5;
        }
       
    }

    // reinit enemy for respawn
    else {
        enemy->iSpeical = enemy->respawnPosition.x > level->player->position.x;
        enemy->position = enemy->respawnPosition;
        enemy->velocity.x = 0;
        enemy->velocity.y = 0;
        enemy->invincible = 0;
        enemy->invTimer = 0.0;
        enemy->hp = enemy->respawnHp;
    }
}

void EP03(Enemy *enemy, MapData *currentMap, Level *level, float deltaTime){
    // change game state to win if boos is dead
    if (enemy->dead == 1 && enemy->type == EN_BOSS2) {
        currentGameState = GAME_STATE_WIN;
        return;
    }
    // invincibility check
    DoEnemyInvCheck(enemy, deltaTime);
    // spawn/Respawn enemy when on screen
    if (IsRectOnScreen(enemy->hitBox, level->camera->camera) && !enemy->active && !enemy->dead){
        enemy->active = 1;
    } 
    // despawn when off screen
    else if ((!IsRectOnScreen(enemy->hitBox, level->camera->camera) && enemy->dead) || !IsRectOnScreenPartial(enemy->hitBox, level->camera->camera)){
        enemy->active = 0;
        enemy->dead = 0;
    } 
    // normal process
    else if (!enemy->dead && enemy->active){
        switch (enemy->cSpecial){
            // wait state
            case 0:
                enemy->facing = GetEnemyFacingToPlayer(enemy, level);
                enemy->iSpeical = !GetEnemyFacingToPlayer(enemy, level); // MovingLeft
                if (!checkEnemyOnGround(enemy, currentMap)){
                    enemy->velocity.y = 480.0;
                } else {
                    enemy->velocity.y = 0.0;
                }
                enemy->dSpecial += deltaTime; // wait timer
                if (enemy->dSpecial >= 0.45 && (float)enemy->hp / (float)enemy->respawnHp < 0.55){
                    enemy->cSpecial = 2;
                    enemy->velocity.y = -1200;
                    enemy->dSpecial = 0;
                } else if (enemy->dSpecial >= 0.75){
                    enemy->cSpecial = 2;
                    enemy->velocity.y = -1200;
                    enemy->dSpecial = 0;
                }
                ApplyEnemyVelocity(enemy, currentMap, deltaTime);
                break;
            // jump to middle state
            case 2:
                if (enemy->iSpeical){
                    enemy->velocity.x = -560.0;
                    enemy->facing = 0;
                } else {
                    enemy->velocity.x = 560.0;
                    enemy->facing = 1;
                }
                if (!checkEnemyOnGround(enemy, currentMap)){
                    if (enemy->velocity.y < 0){
                        enemy->velocity.y += 2400.0 * deltaTime;
                    } else {
                        enemy->velocity.y += 3600.0 * deltaTime;
                    }
                } else {
                    enemy->cSpecial = 3;
                    enemy->spriteX = 0;
                    enemy->velocity.y = 0.0;
                    enemy->velocity.x = 0.0;
                }
                ApplyEnemyVelocity(enemy, currentMap, deltaTime);
                break;
            // shoot circle state
            case 3:
                if (enemy->dSpecial <= 0.0){
                    enemy->dSpecial = 0;
                    for (int i = 0; i <= 180; i += 36){
                        Vector2 pDir = (Vector2){cos((double)i * (PI / 180.0)), sin((double)i * (PI / 180.0))};
                        Vector2 pPos = (Vector2){enemy->hitBox.x + enemy->hitBox.width / 2, enemy->hitBox.y + enemy->hitBox.height / 2};
                        Vector2 pVel = (Vector2){1330.0, -1330.0};
                        pVel = Vector2Multiply(pVel, Vector2Normalize(pDir));
                        AddProjectile(level, MakeProjectile(PROJ_BOSS2, pPos, pVel, (Vector2){24, 24}, (Vector2){21, 24}, enemy->facing));
                    }
                }
                if (enemy->dSpecial >= 0.45 && (float)enemy->hp / (float)enemy->respawnHp < 0.55){
                    enemy->cSpecial = 0;
                    enemy->dSpecial = 0;
                } else if (enemy->dSpecial >= 0.75){
                    enemy->cSpecial = 0;
                    enemy->dSpecial = 0;
                } else {
                    enemy->dSpecial += deltaTime;
                }
                break;
        }
        // Check collision with player
        CheckCollisionWithPlayer(enemy, level);
        // animation stuff
        enemy->spriteY = enemy->facing;
        switch (enemy->cSpecial){
            case 0:
                enemy->spriteX = 0;
                break;
            case 2:
                enemy->spriteX = 1;
                break;
            case 3:
                enemy->spriteX = 0;
                enemy->spriteY += 2;
        }
       
    }

    // reinit enemy for respawn
    else {
        enemy->iSpeical = enemy->respawnPosition.x > level->player->position.x;
        enemy->position = enemy->respawnPosition;
        enemy->velocity.x = 0;
        enemy->velocity.y = 0;
        enemy->invincible = 0;
        enemy->invTimer = 0.0;
        enemy->hp = enemy->respawnHp;
    }
}

void EP04(Enemy *enemy, MapData *currentMap, Level *level, float deltaTime){
    // change game state to win if boos is dead
    if (enemy->dead == 1 && enemy->type == EN_BOSS3) {
        currentGameState = GAME_STATE_WIN;
        return;
    }
    // invincibility check
    DoEnemyInvCheck(enemy, deltaTime);
    // spawn/Respawn enemy when on screen
    if (IsRectOnScreen(enemy->hitBox, level->camera->camera) && !enemy->active && !enemy->dead){
        enemy->active = 1;
    } 
    // despawn when off screen
    else if ((!IsRectOnScreen(enemy->hitBox, level->camera->camera) && enemy->dead) || !IsRectOnScreenPartial(enemy->hitBox, level->camera->camera)){
        enemy->active = 0;
        enemy->dead = 0;
    } 
    // normal process
    else if (!enemy->dead && enemy->active){
        int attackRng = GetRandomValue(0, 256);
        switch (enemy->cSpecial){
            // walking state
            case 0:
                if (enemy->iSpeical && (IsTileAtPositionBlocking(currentMap, enemy->hitBox.x - 8, enemy->hitBox.y + enemy->hitBox.height / 2.0))){
                    enemy->iSpeical = 0;
                    enemy->cSpecial = 1;
                } else if (!enemy->iSpeical && (IsTileAtPositionBlocking(currentMap, enemy->hitBox.x + enemy->hitBox.width + 8, enemy->hitBox.y + enemy->hitBox.height / 2.0))){
                    enemy->iSpeical = 1;
                    enemy->cSpecial = 1;
                }
                if (enemy->iSpeical){
                    enemy->velocity.x = -560.0;
                    enemy->facing = 0;
                } else {
                    enemy->velocity.x = 560.0;
                    enemy->facing = 1;
                }
                if (!checkEnemyOnGround(enemy, currentMap)){
                    enemy->velocity.y = 480.0;
                } else {
                    enemy->velocity.y = 0.0;
                }
                ApplyEnemyVelocity(enemy, currentMap, deltaTime);
                break;
            // shoot state
            case 1:
                if (enemy->dSpecial >= 0.525){
                    enemy->dSpecial = 0;
                    Vector2 pPos = enemy->facing == 0 ? (Vector2){enemy->position.x - 38, enemy->position.y + 32} : (Vector2){enemy->position.x + 46, enemy->position.y + 32};
                    Vector2 pVel = enemy->facing == 0 ? (Vector2){-680.0, -300.0} : (Vector2){680.0, -300.0};
                    AddProjectile(level, MakeProjectile(PROJ_BOSS3, pPos, pVel, (Vector2){24, 24}, (Vector2){21, 24}, enemy->facing));
                    enemy->iSpeical2++;
                    if (enemy->iSpeical2 >= 6){
                        enemy->iSpeical2 = 0;
                        enemy->cSpecial = 0;
                    }
                } else {
                    enemy->dSpecial += deltaTime;
                }
                break;
        }
        // Check collision with player
        CheckCollisionWithPlayer(enemy, level);
        // animation stuff
        enemy->spriteY = enemy->facing;
        switch (enemy->cSpecial){
            case 0:
                 if (enemy->spriteTimer >= 0.1){
                    enemy->spriteTimer = 0;
                    if (enemy->spriteX == 4){
                        enemy->spriteX = 1;
                    } else {
                        enemy->spriteX++;
                    }
                } else {
                    enemy->spriteTimer += deltaTime;
                }
                break;
            case 1:
                enemy->spriteY += 2;
                enemy->spriteX = 0;
                break;
            case 2:
                enemy->spriteX = 5;
        }
       
    }

    // reinit enemy for respawn
    else {
        enemy->iSpeical = enemy->respawnPosition.x > level->player->position.x;
        enemy->position = enemy->respawnPosition;
        enemy->velocity.x = 0;
        enemy->velocity.y = 0;
        enemy->invincible = 0;
        enemy->invTimer = 0.0;
        enemy->hp = enemy->respawnHp;
    }
}

void EP05(Enemy *enemy, MapData *currentMap, Level *level, float deltaTime){
    // change game state to win if boos is dead
    if (enemy->dead == 1 && enemy->type == EN_BOSS4) {
        currentGameState = GAME_STATE_WIN;
        return;
    }
    // invincibility check
    DoEnemyInvCheck(enemy, deltaTime);
    // spawn/Respawn enemy when on screen
    if (IsRectOnScreen(enemy->hitBox, level->camera->camera) && !enemy->active && !enemy->dead){
        enemy->active = 1;
    } 
    // despawn when off screen
    else if ((!IsRectOnScreen(enemy->hitBox, level->camera->camera) && enemy->dead) || !IsRectOnScreenPartial(enemy->hitBox, level->camera->camera)){
        enemy->active = 0;
        enemy->dead = 0;
    } 
    // normal process
    else if (!enemy->dead && enemy->active){
        switch (enemy->cSpecial){
            // walking state
            case 0:

                if (enemy->dSpecial >= 0.65 && (float)enemy->hp / (float)enemy->respawnHp < 0.55){
                    enemy->cSpecial = 1;    // set to charge up state
                    enemy->dSpecial = 0;
                    enemy->spriteX = 0;
                } else if (enemy->dSpecial >= 1.25){
                    enemy->cSpecial = 1;
                    enemy->dSpecial = 0;
                    enemy->spriteX = 0;
                } else {
                    enemy->dSpecial += deltaTime;
                }

                if (enemy->iSpeical && (IsTileAtPositionBlocking(currentMap, enemy->hitBox.x - 8, enemy->hitBox.y + enemy->hitBox.height / 2.0))){
                    enemy->iSpeical = 0;
                } else if (!enemy->iSpeical && (IsTileAtPositionBlocking(currentMap, enemy->hitBox.x + enemy->hitBox.width + 8, enemy->hitBox.y + enemy->hitBox.height / 2.0))){
                    enemy->iSpeical = 1;
                }
                if (enemy->iSpeical2 && (IsTileAtPositionBlocking(currentMap, enemy->hitBox.x + enemy->hitBox.width / 2.0, enemy->hitBox.y - 8) || enemy->position.y <= 29 * GAME_TILE_SIZE)){
                    enemy->iSpeical2 = 0;
                } else if (!enemy->iSpeical2 && (IsTileAtPositionBlocking(currentMap, enemy->hitBox.x + enemy->hitBox.width / 2.0, enemy->hitBox.y + enemy->hitBox.height + 8))){
                    enemy->iSpeical2 = 1;
                }

                if (enemy->iSpeical){
                    enemy->velocity.x = -560.0;
                } else {
                    enemy->velocity.x = 560.0;
                }

                if (enemy->iSpeical2){
                    enemy->velocity.y = -560.0;
                } else {
                    enemy->velocity.y = 560.0;
                }
                ApplyEnemyVelocity(enemy, currentMap, deltaTime);
                break;
            // shoot circle state
            case 2:
                enemy->dSpecial = 0;
                for (int i = 0; i <= 360; i += 36){
                    Vector2 pDir = (Vector2){cos((double)i * (PI / 180.0)), sin((double)i * (PI / 180.0))};
                    Vector2 pPos = (Vector2){enemy->hitBox.x + enemy->hitBox.width / 2, enemy->hitBox.y + enemy->hitBox.height / 2};
                    Vector2 pVel = (Vector2){880.0, -880.0};
                    pVel = Vector2Multiply(pVel, Vector2Normalize(pDir));
                    AddProjectile(level, MakeProjectile(PROJ_BOSS4, pPos, pVel, (Vector2){24, 24}, (Vector2){21, 24}, enemy->facing));
                }
                enemy->cSpecial = 0;
                break;
        }
        // Check collision with player
        CheckCollisionWithPlayer(enemy, level);
        // animation stuff
        switch (enemy->cSpecial){
            case 0:
                 if (enemy->spriteTimer >= 0.1){
                    enemy->spriteTimer = 0;
                    enemy->spriteY = 0;
                    if (enemy->spriteX == 4){
                        enemy->spriteX = 0;
                    } else {
                        enemy->spriteX++;
                    }
                } else {
                    enemy->spriteTimer += deltaTime;
                }
                break;
            case 1:
                if (enemy->spriteTimer >= 0.05){
                    enemy->spriteTimer = 0;
                    enemy->spriteY = 1;
                    if (enemy->spriteX == 4){
                        enemy->spriteX = 0;
                        enemy->cSpecial = 2;
                    } else {
                        enemy->spriteX++;
                    }
                } else {
                    enemy->spriteTimer += deltaTime;
                }
                break;
        }
       
    }

    // reinit enemy for respawn
    else {
        enemy->iSpeical = enemy->respawnPosition.x > level->player->position.x;
        enemy->position = enemy->respawnPosition;
        enemy->velocity.x = 0;
        enemy->velocity.y = 0;
        enemy->invincible = 0;
        enemy->invTimer = 0.0;
        enemy->hp = enemy->respawnHp;
    }
}

void ProcessEnemy(Enemy *enemy, MapData *currentMap, Level *level, float deltaTime){
    switch (enemy->type){
        case EN_WALK:
            EP0(enemy, currentMap, level, deltaTime);
            break;
        case EN_BOSSROOM_TRIGGER:
            EP01(enemy, currentMap, level, deltaTime);
            break;
        case EN_BOSS1:
            EP02(enemy, currentMap, level, deltaTime);
            break;
        case EN_BOSS2:
            EP03(enemy, currentMap, level, deltaTime);
            break;
        case EN_BOSS3:
            EP04(enemy, currentMap, level, deltaTime);
            break;
        case EN_BOSS4:
            EP05(enemy, currentMap, level, deltaTime);
            break;
    }
}

void DrawEnemy(Enemy *enemy){
    switch (enemy->type){
        case EN_BOSS1:
            ED02(enemy);
            break;
        case EN_BOSS2:
            ED02(enemy);
            break;
        case EN_BOSS3:
            ED02(enemy);
            break;
        case EN_BOSS4:
            ED02(enemy);
            break;
        default :
            ED0(enemy);
            break;
    }
}

void UnloadEnemy(Enemy *enemy){
    if (enemy){
        free(enemy);
    }
}

void UnloadEnemyTextures(){
    for (int i = 0; i < MAX_ENEMY_TYPE; i++){
        UnloadTexture(enemyTextures[i]);
    }
}