#ifndef TILESET_H
#define TILESET_H

#include "include/raylib.h"
#include "game_struct.h"
#include <stdlib.h>

TileSet* LoadTileSetFromImage(const char *fileName, int tileSize);
void UnloadTileSet(TileSet *tileSet);

#endif