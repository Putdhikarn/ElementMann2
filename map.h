#ifndef MAP_H
#define MAP_H

#include "tileset.h"
#include "game_def.h"
#include "game_struct.h"
#include <string.h>
#include <ctype.h>
#include <stdio.h>

MapData* LoadMapDataFromFile(const char *fileName);
void UnloadMapData(MapData *mapData);
void SetMapTileSet(const char *fileName, MapData *mapData, int tileSize);

int IsTileAtPositionBlocking(MapData *mapData, float worldX, float worldY);
int IsRectAtPostitionIntersectAnyTile(MapData *mapData, Rectangle rect);
int IsRectAtPostitionNotIntersectAnyTile(MapData *mapData, Rectangle rect);

#endif