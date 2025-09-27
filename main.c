#include "game.h"

int main() {
	
    SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI | FLAG_WINDOW_ALWAYS_RUN);

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Elemant Mann2");

    SetTargetFPS(GetMonitorRefreshRate(0));
    // SetTargetFPS(60);

    GameInit();

    while (!WindowShouldClose()) {
        GameLoop();
    }

    GameCleanUp();

    CloseWindow();
    return 0;
}