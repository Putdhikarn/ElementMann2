#include "win_screen.h"
#include "game_struct.h"
#include "game_def.h"

extern Level *currentLevel;
static WinScreen winScreenInstance;

void WinScreen_Init(WinScreen *ws) {
    ws->panel = LoadTexture("data/sprites/win_panel.png");
    ws->bgAnimId = 0;
    ws->bgFrame = 0;
}

void WinScreen_Update(WinScreen *ws) {
    // เมื่อกด ENTER หรือ ESC → กลับหน้าเลือกด่าน
    if (IsKeyPressed(KEY_X)) {
        // รีเซ็ตตำแหน่งผู้เล่น
        currentLevel->player->position = currentLevel->player->respawnPosition;
        currentLevel->camera->camera.target = currentLevel->player->position;
        currentLevel->camera->followPlayer = 1;
        // ไปหน้าเลือกเลเวล
        currentGameState = GAME_STATE_LEVEL_SELECT;
    }
}

void WinScreen_Draw(WinScreen *ws, Level *level) {
    BeginDrawing();
    ClearBackground(BLACK);

    // แสดง win_panel เต็มจอแบบพอดี
    DrawTexturePro(
        ws->panel,
        (Rectangle){0, 0, ws->panel.width, ws->panel.height},
        (Rectangle){0, 0, SCREEN_WIDTH, SCREEN_HEIGHT},
        (Vector2){0, 0},
        0.0f,
        WHITE
    );

    EndDrawing();
}

void WinScreen_Unload(WinScreen *ws) {
    UnloadTexture(ws->panel);
}

// wrapper
void LoadWinScreen() {
    WinScreen_Init(&winScreenInstance);
}

void ProcessWinScreen() {
    WinScreen_Update(&winScreenInstance);
}

void DrawWinScreen() {
    extern Level *currentLevel;
    WinScreen_Draw(&winScreenInstance, currentLevel);
}

void UnloadWinScreen() {
    WinScreen_Unload(&winScreenInstance);
}
