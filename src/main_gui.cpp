#include "raylib.h"

int main() {
    InitWindow(800, 600, "UNI-GradeManager - GUI");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Benvenuto in UNI-GradeManager", 100, 200, 20, BLACK);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}