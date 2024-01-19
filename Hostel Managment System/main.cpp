#include "ProjectHeader.hpp"

int main(void)
{
    // --------------------- Initialization ---------------------------
    InitWindow(variables::screenWidth, variables::screenHeight, ProjectInfo::appName);
    initializeVariables();
    SetTargetFPS(variables::targetFPS);
    SetExitKey(0);

    while (!variables::shouldExit)
    {
        switch (variables::currentLayer)
        {
        case variables::LOADING_SCREEN:
            loadingScreen();
            break;
        case variables::FATAL_ERROR_SCREEN:
            fatalErrorScreen();
            break;
        case variables::CREATE_NEW_HOSTEL_SCREEN:
            createNewHostelScreen();
            break;
        case variables::HOME_SCREEN:
            homeScreen();
            break;
        case variables::HOSTEL_DETAILS_SCREEN:
            hostelDetailsScreen();
            break;
        case variables::ADD_STUDENT_SCREEN:
            addStudentScreen();
            break;
        case variables::EXIT_SCREEN:
            exitScreen();
            break;
        default:
            fatalErrorScreen();
            break;
        }
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadTexture(variables::fatalErrorTexture);
    UnloadTexture(variables::bugCatTexture);
    UnloadImage(variables::bugCatGIFImage);
    CloseWindow();
    //--------------------------------------------------------------------------------------

    return 0;
}