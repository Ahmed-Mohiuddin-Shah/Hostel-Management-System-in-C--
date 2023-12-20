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
        case variables::STUDENT_DETAILS_SCREEN:
            studentDetailsScreen();
            break;
        case variables::ROOM_DETAILS_SCREEN:
            roomDetailsScreen();
            break;
        case variables::STAFF_DETAILS_SCREEN:
            staffDetailsScreen();
            break;
        case variables::DISPLAY_INVOICES_SCREEN:
            displayInvoicesScreen();
            break;
        case variables::ADD_STUDENT_SCREEN:
            addStudentScreen();
            break;
        case variables::PROMOTE_STUDENTS_SCREEN:
            promoteStudentsScreen();
            break;
        case variables::ADD_ROOM_SCREEN:
            addRoomScreen();
            break;
        case variables::ADD_STAFF_SCREEN:
            addStaffScreen();
            break;
        case variables::REMOVE_STAFF_SCREEN:
            removeStaffScreen();
            break;
        case variables::GENERATE_INVOICES_SCREEN:
            generateInvoicesScreen();
            break;
        case variables::MARK_INVOICE_PAID_SCREEN:
            markInvoicePaidScreen();
            break;
        case variables::GET_SPECIFIC_INVOICE_SCREEN:
            getSpecificInvoiceScreen();
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
    UnloadTexture(variables::successTexture);
    UnloadTexture(variables::errorTexture);
    UnloadTexture(variables::bugCatTexture);
    UnloadImage(variables::bugCatGIFImage);
    CloseWindow();
    //--------------------------------------------------------------------------------------

    return 0;
}