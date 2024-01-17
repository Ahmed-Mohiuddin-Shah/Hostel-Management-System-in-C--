#include "ProjectHeader.hpp"

int main(void)
{
    // --------------------- Initialization ---------------------------
    InitWindow(variables::screenWidth, variables::screenHeight, "raylib [textures] example - gif playing");
    initializeVariables();
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(variables::H_DARK_GREY);
        drawCustomText("Elo!", Vector2{ 10, 10 }, variables::headings, 1, variables::H_WHITE);
        animateGIF(Vector2{ 100, 100 });
        EndDrawing();
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    unloadResources();
    CloseWindow();
    //--------------------------------------------------------------------------------------

    return 0;
}