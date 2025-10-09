#ifndef TILESET_H
#define TILESET_H

#include "include/raylib.h"
#include "game_struct.h"
#include <stdlib.h>

TileSet* LoadTileSetFromImage(const char *fileName, int tileSize);
void DrawTileFromSet(TileSet *TileSet, int tileIndex,int x,int y);
void UnloadTileSet(TileSet *tileSet);

#endif