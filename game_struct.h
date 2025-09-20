#ifndef GAME_STRUCT_H
#define GAME_STRUCT_H

#include "include/raylib.h"
#include <stddef.h>
#include <stdlib.h>

typedef struct {
    Texture2D *tileTextures;
} TileSet;

typedef struct {
    int width, height;
    int *mapData;
    TileSet *tileSet;
} MapData;

typedef enum {
    PROJ_PLAYER_NORMAL
} PROJ_TYPE;

typedef struct Projectile{
    char toBeUnload;

    PROJ_TYPE type;

    Vector2 position;
    Vector2 velocity;

    Rectangle hitBox;
    Vector2 hitBoxOffset;

    float spriteTimer;
    int spriteSize;
    int facing;
    int spriteX;
    int spriteY;

    char hitSomething;
    int iSpeical;
    double dSpecial;

} Projectile;

typedef struct {
    Texture spritesNormal;
    Texture spritesNormalInvincible;

    Rectangle hitBox;
    Vector2 position;
    Vector2 velocity;

    float moveDelayTimer;
    float invincibilityTimer;
    float jumpTimer;

    float shootTimer;
    float shootSpriteTimer;
    int shootSprite;

    float spriteTimer;
    int spriteLeg;
    int spriteLegLast;
    int spriteWalk;
    int spirteX;
    int spirteY;

    int invincible;
    int facing;
    int hp;
    int alive;
    int jumped;
    int onGround;
} Player;

typedef enum {
    EN_WALK
} ENEMY_TYPE;

typedef struct Enemy{
    char toBeUnload;

    ENEMY_TYPE type;

    Vector2 position;
    Vector2 respawnPosition;
    Vector2 velocity;

    Rectangle hitBox;
    Vector2 hitBoxOffset;

    float spriteTimer;
    int spriteSize;
    int facing;
    int spriteX;
    int spriteXLast;
    int spriteY;

    char respawnable;
    char active;
    char dead;

    int respawnHp;
    int hp;
    int iSpeical;
    double dSpecial;

} Enemy;

typedef struct Level{
    Camera2D *camera;
    Projectile *projectiles[256];
    Enemy *enemies[256];
    Player* player;
} Level;

extern int G_PlayerProjCount;

#endif