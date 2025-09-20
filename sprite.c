#include "sprite.h"

Texture* LoadSpritesSheet(const char *fileName, int tileSize){
    // load the source image.
    Image source = LoadImage(fileName);
    // prepare image for slicing.
    int column = source.width / tileSize;
    int row = source.height / tileSize;
    Rectangle sliceRect = {0, 0, tileSize, tileSize};
    Texture* spriteSheet = (Texture *)malloc(sizeof(Texture) * (column * row));
    // slice the image to individual texture.
    Texture *textPt = spriteSheet;
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
    return spriteSheet;
}

void UnloadSpritesSheet(Texture* spriteSheet){
    free(spriteSheet);
}