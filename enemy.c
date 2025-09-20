#include "enemy.h"

Texture enemyTextures[MAX_ENEMY_TYPE];

void LoadEnemyTextures(){
    enemyTextures[EN_WALK] = LoadTexture("./data/sprites/enemy.png");
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

    temp->respawnable = 1;
    temp->active = 0;
    temp->dead = 0;

    temp->iSpeical = 0;
    temp->dSpecial = 0.0;

    switch (type){
        case EN_WALK:
            temp->hitBoxOffset = (Vector2){12, 18};
            temp->hitBox = (Rectangle){temp->position.x + temp->hitBoxOffset.x, temp->position.y + temp->hitBoxOffset.y, 48, 51};
            temp->spriteSize = 72;
            temp->hp = 1;
            temp->respawnHp = temp->hp;
            temp->iSpeical = 1;
            break;
    }

    return temp;
}

int IsRectOnScreen(Rectangle check, Camera2D *camera){
    Rectangle screenRect = (Rectangle){camera->target.x - camera->offset.x, camera->target.y - camera->offset.y, SCREEN_WIDTH, SCREEN_HEIGHT};
    char tL = CheckCollisionPointRec((Vector2){check.x, check.y}, screenRect);
    char tR = CheckCollisionPointRec((Vector2){check.x + check.width, check.y}, screenRect);

    char bL = CheckCollisionPointRec((Vector2){check.x, check.y + check.height}, screenRect);
    char bR = CheckCollisionPointRec((Vector2){check.x + check.width, check.y + check.height}, screenRect);

    return (tL && tR && bL && bR);
}

int IsRectOnScreenPartial(Rectangle check, Camera2D *camera){
    Rectangle screenRect = (Rectangle){camera->target.x - camera->offset.x, camera->target.y - camera->offset.y, SCREEN_WIDTH, SCREEN_HEIGHT};
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
    enemy->hp--;
    if (enemy->hp <= 0){
        if (!enemy->respawnable){
            enemy->toBeUnload = 1;
        }
        enemy->dead = 1;
    }
}

void CheckCollisionWithPlayer(Enemy *enemy, Level *level){
    if (CheckCollisionRecs(enemy->hitBox, level->player->hitBox)){
        DoPlayerHit(level->player, (Vector2){enemy->hitBox.x + (enemy->hitBox.width / 2), enemy->hitBox.y});
    }
}

void EP0(Enemy *enemy, MapData *currentMap, Level *level, float deltaTime){
    // spawn/Respawn enemy when on screen
    if (IsRectOnScreen(enemy->hitBox, level->camera) && !enemy->active && !enemy->dead){
        enemy->active = 1;
    } 
    // despawn when off screen
    else if ((!IsRectOnScreen(enemy->hitBox, level->camera) && enemy->dead) || !IsRectOnScreenPartial(enemy->hitBox, level->camera)){
        enemy->active = 0;
        enemy->dead = 0;
    } 
    // normal process
    else if (!enemy->dead && enemy->active){
        if (enemy->iSpeical && (!IsTileAtPositionBlocking(currentMap, enemy->hitBox.x - 2, enemy->hitBox.y + enemy->hitBox.height + 16) || 
            IsTileAtPositionBlocking(currentMap, enemy->hitBox.x - 4, (enemy->hitBox.y + enemy->hitBox.height) / 2.0))){
                enemy->iSpeical = 0;
        } else if (!enemy->iSpeical && (!IsTileAtPositionBlocking(currentMap, enemy->hitBox.x + enemy->hitBox.width + 2, enemy->hitBox.y + enemy->hitBox.height + 16) ||
            IsTileAtPositionBlocking(currentMap, enemy->hitBox.x + enemy->hitBox.width + 4, (enemy->hitBox.y + enemy->hitBox.height) / 2.0))){
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
        enemy->hp = enemy->respawnHp;
    }
}

void ED0(Enemy *enemy){
    if (!enemy->dead && enemy->active){
        DrawTextureRec(enemyTextures[enemy->type], (Rectangle){enemy->spriteX * enemy->spriteSize, enemy->spriteY * enemy->spriteSize, enemy->spriteSize, enemy->spriteSize}, enemy->position, WHITE);
    }
}

void ProcessEnemy(Enemy *enemy, MapData *currentMap, Level *level, float deltaTime){
    switch (enemy->type){
        case EN_WALK:
            EP0(enemy, currentMap, level, deltaTime);
            break;
    }
}

void DrawEnemy(Enemy *enemy){
    switch (enemy->type){
        case EN_WALK:
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