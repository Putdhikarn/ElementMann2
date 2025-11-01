#ifndef GAME_DEF_H
#define GAME_DEF_H

#define SCREEN_WIDTH 1152
#define SCREEN_HEIGHT 672

#define GAME_TILE_SIZE 48

#define SNAP_TO_TILE_POS(x) (((int)x / 48) * 48)

#define GAME_PROCESS_FPS 60

#define COLOR_LEVEL_1 CLITERAL(Color){176, 168, 61, 255}
#define COLOR_LEVEL_2 CLITERAL(Color){51, 38, 15, 255}
#define COLOR_LEVEL_3 CLITERAL(Color){34, 60, 111, 255}
#define COLOR_LEVEL_4 CLITERAL(Color){58, 33, 77, 255}

#endif