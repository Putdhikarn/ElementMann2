#ifndef SPRITE_H
#define SPRITE_H

#include "include/raylib.h"
#include <stdlib.h>

Texture* LoadSpritesSheet(const char *fileName, int tileSize);
void UnloadSpritesSheet(Texture* spriteSheet);

#endif