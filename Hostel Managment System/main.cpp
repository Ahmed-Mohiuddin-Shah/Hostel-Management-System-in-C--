#include "ProjectHeader.hpp"

int main(void)
{
    // --------------------- Initialization ---------------------------
    InitWindow(variables::screenWidth, variables::screenHeight, ProjectInfo::appName);
    initializeVariables();
    SetTargetFPS(variables::targetFPS);

    while (!WindowShouldClose())
    {
        switch (variables::currentLayer)
        {
        case variables::LOADING_SCREEN:
            loadingScreen();
            break;
        case variables::FATAL_ERROR:
            fatalErrorScreen();
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