#ifndef GAME_STRUCT_H
#define GAME_STRUCT_H

#include "include/raylib.h"
#include "include/raymath.h"
#include <stddef.h>
#include <stdlib.h>

typedef enum {
    GAME_STATE_MAIN_MENU,
    GAME_STATE_LEVEL_SELECT,
    GAME_STATE_PASSWORD,
    GAME_STATE_LEVEL,
    GAME_STATE_WIN
} GAME_STATE;

typedef struct {
    Texture2D texture;
    int tileSize;
} TileSet;

typedef struct {
    int width, height;
    int *mapData;
    TileSet *tileSet;
} MapData;

typedef enum {
    PROJ_PLAYER_NORMAL,
    PROJ_BOSS1,
    PROJ_BOSS1_2,
    PROJ_BOSS2
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
    Vector2 respawnPosition;
    Vector2 velocity;

    float moveDelayTimer;
    float invincibilityTimer;
    float respawnTimer;
    float jumpTimer;

    float shootTimer;
    float shootSpriteTimer;
    int shootSprite;
    char invSpriteCounter;

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
    EN_WALK,
    EN_BOSSROOM_TRIGGER,
    EN_BOSS1,
    EN_BOSS2,
    EN_BOSS3,
    EN_BOSS4
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

    char invincible;
    float invTimer;

    char respawnable;
    char active;
    char dead;

    int respawnHp;
    int hp;
    char cSpecial;
    char cSpecial2;
    int iSpeical;
    int iSpeical2;
    double dSpecial;

} Enemy;

typedef struct GameCamera{
    Camera2D camera;
    char followPlayer;
} GameCamera;

typedef struct Level{
    GameCamera *camera;
    Projectile *projectiles[256];
    Enemy *enemies[64];
    Player* player;
} Level;



extern int G_PlayerProjCount;
extern GAME_STATE currentGameState;

#endif