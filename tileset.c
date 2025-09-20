#include "tileset.h"

TileSet* LoadTileSetFromImage(const char *fileName, int tileSize){
    TileSet* tileSet = malloc(sizeof(TileSet));
    // load the source image.
    Image source = LoadImage(fileName);
    // prepare image for slicing.
    int column = source.width / tileSize;
    int row = source.height / tileSize;
    tileSet->tileTextures = (Texture *)malloc(sizeof(Texture) * (column * row));
    Rectangle sliceRect = {0, 0, tileSize, tileSize};
    // slice the image to texture.
    Texture *textPt = tileSet->tileTextures;
    for (int r = 0; r < row; r++){
        for (int c = 0; c < column; c++){
            sliceRect.x = c * tileSize;
            sliceRect.y = r * tileSize;
            Image sliced = ImageFromImage(source, sliceRect);
            *textPt = LoadTextureFromImage(sliced);
            textPt++;
            UnloadImage(sliced);
        }
    }

    UnloadImage(source);
    return tileSet;
}
void UnloadTileSet(TileSet *tileSet){
    UnloadTexture(*tileSet->tileTextures);
    free(tileSet);
}