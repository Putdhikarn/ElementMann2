#include "map.h"
#define STATE_HEADER 0
#define STATE_MAP 1

MapData* LoadMapDataFromFile(const char *fileName){
    MapData *mapData;
    FILE *file = fopen(fileName, "r");
    if (file == NULL){
        TraceLog(LOG_ERROR, "Map File Not Found.");
        return mapData;
    }

    int currentMapState = 0;
    int width = 0, height = 0;
    int mapReadRow = 0;
    char line[2048];
    // reads the file line by line.
    while (fgets(line, sizeof(line), file)){
        // trim newline.
        line[strcspn(line, "\r\n")] = 0;
        // set the parse state according to the section.
        if(strcmp(line, "[HEADER]") == 0){
            currentMapState = STATE_HEADER;
            continue;
        } else if (strcmp(line, "[MAPDATA]") == 0){
            currentMapState = STATE_MAP;
            // got width and height so the [HEADER] has been read, allocate the mapData stuff.
            if (width > 0 && height > 0){
                mapData = (MapData *)malloc(sizeof(MapData));
                mapData->width = width;
                mapData->height = height;
                mapData->mapData = (int *)calloc(width * height, sizeof(int));

                if (mapData->mapData == NULL){
                    fclose(file);
                    TraceLog(LOG_ERROR, "Invalid Map Size!");
                    return mapData;
                }
            } else {
                fclose(file);
                TraceLog(LOG_ERROR, "Map File Missing [HEADER]!");
                return mapData;
            }
            continue;
        } 
        // parse the map data according to the current state
        switch (currentMapState){
            case STATE_HEADER:
                if (strncmp(line, "WIDTH=", 6) == 0){
                    width = atoi(line + 6);
                } else if (strncmp(line, "HEIGHT=", 7) == 0){
                    height = atoi(line + 7);
                }
                break;
            case STATE_MAP:
                int col = 0;
                char *ltk = strtok(line, ",");
                // parse the line
                while (ltk != NULL && col < width){
                    mapData->mapData[mapReadRow * width + col] = atoi(ltk);
                    ltk = strtok(NULL, ",");
                    col++;
                }
                mapReadRow++;
                break;
            default:
                break;
        }
    }
    fclose(file);
    if (mapReadRow != height){
        TraceLog(LOG_ERROR, TextFormat("Map Read Row Don't Match Map Height! %d != %d", mapReadRow, height));
        free(mapData->mapData);
        return mapData;
    }
    return mapData;
}

void SetMapTileSet(const char *fileName, MapData *mapData, int tileSize){
    mapData->tileSet = LoadTileSetFromImage(fileName, tileSize);
}

void UnloadMapData(MapData *mapData){
    if (mapData->tileSet){
        UnloadTileSet(mapData->tileSet);
    }
    if (mapData->mapData){
        free(mapData->mapData);
    }
    free(mapData);
}

int IsTileAtPositionBlocking(MapData *mapData, float worldX, float worldY){
    int col = (int)worldX / 48;
    int row = (int)worldY / 48;
    // TraceLog(LOG_INFO, TextFormat("%d %d %d %d",col,row, *(mapData->mapData + (row * mapData->width + col)),*(mapData->mapData + (row * mapData->width + col)) > 0));
    int tileId = *(mapData->mapData + (row * mapData->width + col));
    return tileId > 0 && tileId <= 17;
}

int IsRectAtPostitionIntersectAnyTile(MapData *mapData, Rectangle rect){
    int topLeft = IsTileAtPositionBlocking(mapData, rect.x, rect.y);
    int topRight = IsTileAtPositionBlocking(mapData, rect.x + rect.width, rect.y);

    int botLeft = IsTileAtPositionBlocking(mapData, rect.x, rect.y + rect.height);
    int botRight = IsTileAtPositionBlocking(mapData, rect.x + rect.width, rect.y + rect.height);

    return (topLeft || topRight || botLeft || botRight);
}

int IsRectAtPostitionNotIntersectAnyTile(MapData *mapData, Rectangle rect){
    int topLeft = IsTileAtPositionBlocking(mapData, rect.x, rect.y);
    int topRight = IsTileAtPositionBlocking(mapData, rect.x + rect.width, rect.y);

    int botLeft = IsTileAtPositionBlocking(mapData, rect.x, rect.y + rect.height);
    int botRight = IsTileAtPositionBlocking(mapData, rect.x + rect.width, rect.y + rect.height);

    return (!topLeft && !topRight && !botLeft && !botRight);
}