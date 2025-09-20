#include "map.h"

MapData LoadMapDataFromFile(const char *fileName){
    MapData mapData = {0, 0};
    FILE *file = fopen(fileName, "r");

    mapData.width = 27;
    mapData.height = 15;
    mapData.mapData = (int *)calloc(mapData.width * mapData.height, sizeof(int));

    int row = 0;
    char line[2048];
    // reads the file line by line.
    while (fgets(line, sizeof(line), file)){
        int col = 0;
        char *ltk = strtok(line, ",");
        // parse the line
        while (ltk != NULL){
            mapData.mapData[row * mapData.width + col] = atoi(ltk);
            ltk = strtok(NULL, ",");
            col++;
        }
        row++;
    }

    fclose(file);
    return mapData;
}

void UnloadMapData(MapData *mapData){
    // if (&mapData->tileSet){
    //     UnloadTileSet(&mapData->tileSet);
    // }
    if (&(mapData->mapData)){
        free(&(mapData->mapData));
    }
    free(mapData);
}