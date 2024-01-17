#include "ProjectHeader.hpp"

int main(void)
{
    // --------------------- Initialization ---------------------------
    InitWindow(variables::screenWidth, variables::screenHeight, "raylib [textures] example - gif playing");
    initializeVariables();
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        switch (variables::currentLayer)
        {
        case variables::LOADING_SCREEN:
            loadingScreen();
            break;
        }
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    unloadResources();
    CloseWindow();
    //--------------------------------------------------------------------------------------

    return 0;
}