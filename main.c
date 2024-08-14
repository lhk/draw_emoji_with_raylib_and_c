#include "raylib.h"
#include <stdio.h>
#include <string.h>

// codepoints to be loaded from an emoji font.
// for experimenting, I'm just using the basic grinning face emoji.
const unsigned int codepoints[] = {
    0x1F600, // 😀 Grinning Face
    // 0x1F370, // 🍰 Shortcake
};

// I'd like to see how the codepoints print when converted to a char array.
// This function is meant to convert an array of codepoints to a char array containing an UTF-8 string.
// DISCLAIMER: I didn't write this, chatgpt spat it out for me.
void CodepointsToUTF8(const unsigned int *codepoints, int length, char *output)
{
    int i, j = 0;
    for (i = 0; i < length; i++)
    {
        if (codepoints[i] <= 0x7F)
        {
            output[j++] = codepoints[i];
        }
        else if (codepoints[i] <= 0x7FF)
        {
            output[j++] = 0xC0 | ((codepoints[i] >> 6) & 0x1F);
            output[j++] = 0x80 | (codepoints[i] & 0x3F);
        }
        else if (codepoints[i] <= 0xFFFF)
        {
            output[j++] = 0xE0 | ((codepoints[i] >> 12) & 0x0F);
            output[j++] = 0x80 | ((codepoints[i] >> 6) & 0x3F);
            output[j++] = 0x80 | (codepoints[i] & 0x3F);
        }
        else if (codepoints[i] <= 0x10FFFF)
        {
            output[j++] = 0xF0 | ((codepoints[i] >> 18) & 0x07);
            output[j++] = 0x80 | ((codepoints[i] >> 12) & 0x3F);
            output[j++] = 0x80 | ((codepoints[i] >> 6) & 0x3F);
            output[j++] = 0x80 | (codepoints[i] & 0x3F);
        }
    }
    output[j] = '\0';
}

int main(void)
{
    const int screenWidth = 400;
    const int screenHeight = 200;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
    SetTargetFPS(60);

    // Various attempts at loading a Font with emojis.
    // I suspect that Noto_Color_Emoji is somehow fundamentally incompatible with MacOS, since the builtin Fontbook application can't load the font either.
    // So I switched to fonts from the OpenMoji project. There's plenty of options, as far as I can tell, the version with untouched svg graphics should be the most compatible.
    // const Font emojiFont = LoadFontEx("../resources/Noto_Color_Emoji/NotoColorEmoji-Regular.ttf", 32, codepoints, 1);
    const Font emojiFont = LoadFontEx("../resources/OpenMoji-color-untouchedsvgz.ttf", 32, codepoints, 1);

    // for sanity checking, I'm also loading the symbola font used in one of the raylib examples.
    // it contains a selection of emoji, such as the grinning face.
    const Font symbolaFont = LoadFont("../resources/symbola.fnt");

    // for sanity checking, I'm setting up a char array for "😀" twice: once directly with a string literal and once by converting my codepoint.
    const char *emoji = "😀";
    char emojiFromCodepoints[5]; // Max 4 bytes for a single UTF-8 character + null terminator
    CodepointsToUTF8(codepoints, 1, emojiFromCodepoints);

    // both of these print 😀
    printf("emoji: %s\n", emoji);
    printf("emojiFromCodepoints: %s\n", emojiFromCodepoints);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        // this works, the emoji is displayed correctly.
        DrawTextEx(symbolaFont, emoji, (Vector2){200, 0}, 50, 1, LIGHTGRAY);
        DrawTextEx(symbolaFont, emojiFromCodepoints, (Vector2){200, 50}, 50, 1, LIGHTGRAY);

        // this doesn't work
        DrawTextEx(emojiFont, emoji, (Vector2){200, 100}, 50, 1, LIGHTGRAY);
        DrawTextEx(emojiFont, emojiFromCodepoints, (Vector2){200, 150}, 50, 1, LIGHTGRAY);
        EndDrawing();
    }
    UnloadFont(emojiFont);
    UnloadFont(symbolaFont);
    CloseWindow(); // Close window and OpenGL context

    return 0;
}