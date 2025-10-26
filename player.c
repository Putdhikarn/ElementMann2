#include "player.h"

#define APPLY_SPEED_X_LIMIT 32.0
#define APPLY_SPEED_Y_MIN -8.0
#define APPLY_SPEED_Y_MAX 8.0

#define MOVE_SPEED_Y_MIN -1500.0
#define MOVE_SPEED_Y_MAX 1700.0

#define MOVE_SPEED_STEP 240.0
#define MOVE_SPEED_WALK 400.0
#define KNOCK_BACK_FORCE 1000.0
#define KNOCK_BACK_DECEL 2440.0

#define SHORT_JUMP_FORCE 360.0
#define JUMP_FORCE_ACCEL 14000.0

#define GRAVITY 3600.0

#define MAX_INVIN_TIME 0.46
#define MAX_RESPAWN_TIME 0.46

#define MAX_HP 8

Player* LoadPlayer(float topLeftX, float topLeftY){
    Player *player = (Player *)malloc(sizeof(Player));
    player->spritesNormal = LoadTexture("data/sprites/player.png");
    player->spritesNormalInvincible = LoadTexture("data/sprites/player_inv.png");

    player->position = (Vector2){topLeftX, topLeftY};
    player->velocity = (Vector2){0.0, 0.0};
    player->respawnPosition = player->position;
    player->hitBox = (Rectangle){topLeftX + 12, topLeftY + 6, 51, 63};

    player->spriteTimer = 0.0;
    player->spirteX = 0;
    player->spirteY = 0;
    player->spriteLeg = 0;
    player->spriteLegLast = 0;
    player->spriteWalk = 0;

    player->invSpriteCounter = 0;
    player->moveDelayTimer = 0.0;
    player->invincibilityTimer = 0.0;
    player->respawnTimer = 0.0;
    player->jumpTimer = 0.0;

    player->shootTimer = 0.0;
    player->shootSpriteTimer = 0.0;
    player->shootSprite = 0;

    player->invincible = 0;
    player->facing = 0;
    player->hp = MAX_HP;
    player->alive = 1;
    player->jumped = 0;
    player->onGround = 0;

    return player;
}

int count = 0;
float countDelta = 0.0;

void ProcessPlayer(Player *player, MapData *currentMap, Level *currentLevel, float deltaTime){
    // TraceLog(LOG_INFO, TextFormat("*%f %f", player->velocity.x, player->velocity.y));
    // TraceLog(LOG_INFO, TextFormat("*%d %f", player->invincible, player->invincibilityTimer));
    // TraceLog(LOG_INFO, TextFormat("*%f %d", player->respawnTimer, currentLevel->camera->followPlayer));
    // countDelta += deltaTime;
    // count++;
    // Shoot
    if (player->alive){
        if (IsKeyPressed(CONTROL_CANCEL)){
            if (player->shootTimer >= 0.02 && G_PlayerProjCount < 3){
                G_PlayerProjCount++;
                player->shootTimer = 0;
                player->shootSprite = 2;
                player->shootSpriteTimer = 0.0;
                Vector2 pPos = player->facing == 0 ? (Vector2){player->position.x - 32, player->position.y + 3} : (Vector2){player->position.x + 40, player->position.y + 3};
                Vector2 pVel = player->facing == 0 ? (Vector2){-1440.0, 0.0} : (Vector2){1440.0, 0.0};

                AddProjectile(currentLevel, MakeProjectile(PROJ_PLAYER_NORMAL, pPos, pVel, (Vector2){24, 24}, (Vector2){21, 24}, player->facing));
                PlaySFX(SFX_ATTACK);
            }
        }
        // Jump
        if (IsKeyDown(CONTROL_CONFIRM) && !(player->invincible && player->invincibilityTimer < MAX_INVIN_TIME)){
            if (!player->jumped){
                player->velocity.y = -SHORT_JUMP_FORCE;
                player->jumped = 1;
                player->jumpTimer = 0.0;
                PlaySFX(SFX_JUMP);
            } else if (player->jumpTimer <= 0.07){
                player->velocity.y -= JUMP_FORCE_ACCEL * deltaTime;
                player->jumpTimer += deltaTime;
            }
        }
        // Movement
        if (IsKeyDown(CONTROL_RIGHT) && !(player->invincible && player->invincibilityTimer < MAX_INVIN_TIME)){
            if (player->moveDelayTimer == 0){
                player->velocity.x = MOVE_SPEED_STEP;
                player->moveDelayTimer += deltaTime;
            } else if (player->moveDelayTimer < 0.14){
                player->velocity.x = 0;
                player->moveDelayTimer += deltaTime;
                player->spriteWalk = 1;
            } else {
                player->velocity.x = MOVE_SPEED_WALK;
                player->spriteWalk = 2;
                player->spriteTimer += deltaTime;
            }
            player->facing = 1;
        } else if (IsKeyDown(CONTROL_LEFT) && !(player->invincible && player->invincibilityTimer < MAX_INVIN_TIME)){
            if (player->moveDelayTimer == 0){
                player->velocity.x = -MOVE_SPEED_STEP;
                player->moveDelayTimer += deltaTime;
            } else if (player->moveDelayTimer < 0.14){
                player->velocity.x = 0;
                player->moveDelayTimer += deltaTime;
                player->spriteWalk = 1;
            } else {
                player->velocity.x = -MOVE_SPEED_WALK;
                player->spriteWalk = 2;
                player->spriteTimer += deltaTime;
            }
            player->facing = 0;
        }
        // Knock back 
        else if (player->invincible){
            if (abs(player->velocity.x) > 0){
                if (player->velocity.x > 0){
                    player->velocity.x += -KNOCK_BACK_DECEL * deltaTime;
                } else {
                    player->velocity.x += KNOCK_BACK_DECEL * deltaTime;
                }
            }
            player->moveDelayTimer = 0;
            if (!player->jumped){
                player->spriteLeg = 0;
                player->spriteWalk = 0;
            }
        } else {
            player->moveDelayTimer = 0.0;
            player->velocity.x = 0;
            player->spriteWalk = 0;
            player->spriteLeg = 0;
        }
        // Ground Check and Gravity
        if (!player->jumped){
            if (!checkPlayerOnGround(player, currentMap)){
                player->jumped = 1;
            }
        } else {
            if (checkPlayerOnGround(player, currentMap) && player->velocity.y >= 0.0){
                player->jumped = 0;
                player->velocity.y = 0;
            } else {
                player->velocity.y += GRAVITY * deltaTime;
            }
        }
        // Change the player sprite to falling if not on ground
        if (!checkPlayerOnGround(player, currentMap) || player->jumped){
            player->spriteWalk = 5;
        }

        if (player->shootTimer < 0.02){
            player->shootTimer += deltaTime;
        }
        // Invincibility Check
        if (player->invincible){
            if (player->invincibilityTimer >= MAX_INVIN_TIME){
                player->invincible = 0;
                player->invincibilityTimer = 0;
            } else {
                player->invincibilityTimer += deltaTime;
            }
        }

        ApplyPlayerVelocity(player, currentMap, deltaTime);
        AnimatePlayerSprite(player, deltaTime);
    } else {
        // Invincibility Check
        if (player->invincible){
            if (player->invincibilityTimer >= MAX_INVIN_TIME){
                player->invincible = 0;
                player->invincibilityTimer = 0;
            } else {
                player->invincibilityTimer += deltaTime;
            }
        }
        // Respawn Player
        if (player->respawnTimer >= MAX_RESPAWN_TIME){
            player->respawnTimer = 0;
            player->hp = MAX_HP;
            player->alive = 1;
            player->velocity.x = 0.0;
            player->velocity.y = 0.0;
            player->invincibilityTimer = 0.0;
            player->invincible = 0;
            player->position = player->respawnPosition;
            currentLevel->camera->followPlayer = 1;
            currentLevel->camera->camera.target.x = player->position.x;
            currentLevel->camera->camera.target.y = player->position.y;
        } else {
            player->respawnTimer += deltaTime;
        }
    }
    
}

// Apply the Player Velocity to Player Position (And do some hitbox magics so the player won't go though a tile)
void ApplyPlayerVelocity(Player *player, MapData *currentMap, float deltaTime){
    player->velocity.y = player->velocity.y > MOVE_SPEED_Y_MAX ? MOVE_SPEED_Y_MAX : player->velocity.y;
    player->velocity.y = player->velocity.y < MOVE_SPEED_Y_MIN ? MOVE_SPEED_Y_MIN : player->velocity.y;

    Vector2 applyVelocity = {player->velocity.x * deltaTime, player->velocity.y * deltaTime};
    // limit the player velocity
    // applyVelocity.x = applyVelocity.x > APPLY_SPEED_X_LIMIT ? APPLY_SPEED_X_LIMIT : applyVelocity.x;
    // applyVelocity.x = applyVelocity.x < -APPLY_SPEED_X_LIMIT ? -APPLY_SPEED_X_LIMIT : applyVelocity.x;

    // applyVelocity.y = applyVelocity.y > APPLY_SPEED_Y_MAX ? APPLY_SPEED_Y_MAX : applyVelocity.y;
    // applyVelocity.y = applyVelocity.y < APPLY_SPEED_Y_MIN ? APPLY_SPEED_Y_MIN : applyVelocity.y;

    // apply x
    // check if the player will overlap the any-tile with the current velocity, 
    // modify the velocity so that the player won't overlap and get stuck inside a tile
    if (!IsRectAtPostitionNotIntersectAnyTile(currentMap, (Rectangle){player->hitBox.x + applyVelocity.x, player->hitBox.y, player->hitBox.width, player->hitBox.height})){
        // int tileSnapX = 0;
        // if (player->velocity.x > 0){
            // tileSnapX = ((player->hitBox.x + player->hitBox.width + player->velocity.x + 2.0) / 48) * 48;
            // player->velocity.x = ((player->hitBox.x + player->hitBox.width + 1) - tileSnapX) * -1;
            // TraceLog(LOG_INFO, TextFormat("%f", player->velocity.x));
        // } else {
            // tileSnapX = (((player->hitBox.x + player->velocity.x - 2) / 48) * 48) + 48;
            // player->velocity.x = ((player->hitBox.x + 36) - tileSnapX) * -1;
        // }
        applyVelocity.x = 0;
    }
    // apply y
    // check if the player will overlap the any-tile with the current velocity, 
    // modify the velocity so that the player won't overlap and get stuck inside a tile
    if (!IsRectAtPostitionNotIntersectAnyTile(currentMap, (Rectangle){player->hitBox.x, player->hitBox.y + applyVelocity.y, player->hitBox.width, player->hitBox.height})) {
    //     float tileSnapY = 0;
    //     if (player->velocity.y > 0) {
    //         tileSnapY = ((player->hitBox.y + player->hitBox.height + player->velocity.y + 4.0) / 48.0) * 48;
    //         player->velocity.y = (((player->hitBox.y + player->hitBox.height + 1) - tileSnapY) * -1);
    //     } else {
    //         tileSnapY = (((player->hitBox.y + player->velocity.y - 4) / 48.0) * 48) + 48;
    //         player->velocity.y = abs(((player->hitBox.y - 1) - tileSnapY));
    //     }
        if (applyVelocity.y > 0){
            applyVelocity.y = ((((int)(player->hitBox.y + player->hitBox.height + applyVelocity.y) / GAME_TILE_SIZE) * GAME_TILE_SIZE) - (player->hitBox.y + player->hitBox.height + 1));
            player->velocity.y = 0;
        } else {
            // TraceLog(LOG_INFO, TextFormat("%f %f %f", applyVelocity.y, (((player->hitBox.y + applyVelocity.y) / GAME_TILE_SIZE) * GAME_TILE_SIZE) + GAME_TILE_SIZE, player->hitBox.y));
            applyVelocity.y = ((((int)(player->hitBox.y + applyVelocity.y) / GAME_TILE_SIZE) * GAME_TILE_SIZE) + GAME_TILE_SIZE) - (player->hitBox.y - 1);
            player->velocity.y = 0;
            // TraceLog(LOG_INFO, TextFormat("%f", applyVelocity.y));
        }
    }

    // TraceLog(LOG_INFO, TextFormat("%d", IsTileAtPositionBlocking(currentMap, player->position.x, player->position.y)));
    // IsTileAtPositionBlocking(currentMap, player->hitBox.x, player->hitBox.y);
    // IsTileAtPositionBlocking(currentMap, player->hitBox.x, player->hitBox.y + player->hitBox.height);
    // TraceLog(LOG_INFO, TextFormat("*%f %f %d", applyVelocity.x, applyVelocity.y, checkPlayerOnGround(player, currentMap)));

    player->position.x += applyVelocity.x;
    player->position.y += applyVelocity.y;

    player->hitBox.x = player->position.x + 12;
    player->hitBox.y = player->position.y + 6;
}

int checkPlayerOnGround(Player *player, MapData *currentMap){
    int botLeft = IsTileAtPositionBlocking(currentMap, player->hitBox.x, player->hitBox.y + player->hitBox.height + 2); 
    int botRight = IsTileAtPositionBlocking(currentMap, player->hitBox.x + player->hitBox.width, player->hitBox.y + player->hitBox.height + 2);

    return botRight || botLeft;
}

void AnimatePlayerSprite(Player *player, float deltaTime){
    // TraceLog(LOG_INFO, TextFormat("%f", player->spriteTimer));
    // shooting
    if (player->shootSpriteTimer >= 0.27){
        player->shootSprite = 0;
    } else {
        player->shootSpriteTimer += deltaTime;
    }
    // walking
    if (!player->jumped){
        if (player->spriteTimer >= 0.14){
            player->spriteTimer = 0;
            // alternate player walking leg
            if (player->spriteLeg == 0){
                player->spriteLeg = player->spriteLegLast == 2 ? 1 : 2;
                player->spriteLegLast = player->spriteLeg; 
            } else {
                player->spriteLeg = 0;
            }
        }
    } else {
        player->spriteTimer = 0;
        player->spriteLeg = 0;
        player->spriteLegLast = player->spriteLeg;
    }
    player->spirteY = player->facing + player->shootSprite;
    player->spirteX = player->spriteWalk + player->spriteLeg;
}

void DoPlayerHit(Player *player, Vector2 hitPos){
    if (player->invincible == 0){
        player->velocity.x = 0;
        if (hitPos.x < player->hitBox.x + player->hitBox.width / 2){
            player->velocity.x = KNOCK_BACK_FORCE;
        } else {
            player->velocity.x = -KNOCK_BACK_FORCE;       
        }
        player->hp--;
        if (player->hp > 0){
            player->invincible = 1;
        } else {
            if(player->alive){
                player->alive = 0;
            }
            PlaySFX(SFX_PLAYER_DEAD);
        }
    }
}

void DrawPlayer(Player *player){
    if (player->alive){
        Rectangle drawRect = (Rectangle){player->spirteX * 72, player->spirteY * 72, 72, 72};
        // TraceLog(LOG_INFO, TextFormat("*%u", &player->spritesNormal));
        if (player->invincible && (int)(player->invincibilityTimer * 100000) % 2 == 0){
            DrawTextureRec(player->spritesNormalInvincible, drawRect, player->position, WHITE);
            player->invSpriteCounter = 0;
        } else {
            DrawTextureRec(player->spritesNormal, drawRect, player->position, WHITE);
            player->invSpriteCounter++;
        }
        // DrawTextureV(player->spritesNormal, player->position, WHITE);
    }
}

void UnloadPlayer(Player *player){
    UnloadTexture(player->spritesNormal);
    UnloadTexture(player->spritesNormalInvincible);
    free(player);
    player = NULL;
}