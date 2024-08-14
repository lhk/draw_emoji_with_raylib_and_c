#include "raylib.h"

int main(void)
{
    const int screenWidth = 400;
    const int screenHeight = 200;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
    SetTargetFPS(60);

    const Font emojiFont = LoadFont("resources/Noto_Color_Emoji/NotoColorEmoji-Regular.ttf");

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawTextEx(emojiFont, "😀", (Vector2){200, 100}, 50, 1, LIGHTGRAY);
        EndDrawing();
    }
    UnloadFont(emojiFont);
    CloseWindow(); // Close window and OpenGL context
}