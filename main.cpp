#include <iostream>
#include "raylib.h"

using namespace std;

int main() {
    const int screenWidth = 1200;
    const int screenHeight = 800;

    InitWindow(screenWidth, screenHeight, "Game of Life");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
        // separate line
        DrawLineEx(Vector2{800, 0}, Vector2{800, 800}, 10.0f, BLACK);

        // drawing the grid
        for (int i = 0; i < 800; i += 10) {
            DrawLineEx(Vector2{(float)i, 0}, Vector2{(float)i, screenHeight}, 1.0f, BLACK);
        }
        for (int i = 0; i < screenHeight; i += 10) {
            DrawLineEx(Vector2{0, (float)i}, Vector2{800, (float)i}, 1.0f, BLACK);
        }

        // drawing the cells
        ClearBackground(RAYWHITE);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
