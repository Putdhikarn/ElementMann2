#include "tileset.h"
#define TILE_ID_BASE 0

TileSet* LoadTileSetFromImage(const char *fileName, int tileSize){
    TileSet* tileSet = malloc(sizeof(TileSet));
    // load the source image.
    tileSet->texture = LoadTexture(fileName); // โหลดภาพใหญ่เพียงครั้งเดียว
    tileSet->tileSize = tileSize;
    return tileSet;
}
void DrawTileFromSet(TileSet *tileSet, int tileIndex, int x, int y){
    if (!tileSet) return;
    if (TILE_ID_BASE == 1 && tileIndex <= 0) return;

    int idx = tileIndex - TILE_ID_BASE;

    int tilesPerRow = tileSet->texture.width  / tileSet->tileSize;
    int tilesPerCol = tileSet->texture.height / tileSet->tileSize;
    int totalTiles  = tilesPerRow * tilesPerCol;

    if (idx < 0 || idx >= totalTiles) return;

    int c = idx % tilesPerRow;
    int r = idx / tilesPerRow;

    Rectangle src = { c * tileSet->tileSize, r * tileSet->tileSize,
                      tileSet->tileSize, tileSet->tileSize };
    DrawTextureRec(tileSet->texture, src, (Vector2){x, y}, WHITE);
}
void UnloadTileSet(TileSet *tileSet){
    UnloadTexture(tileSet->texture);
    free(tileSet);
}