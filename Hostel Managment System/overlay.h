#pragma once

// -------------- Overlay ------------------------
void guiOverlay() {
    using namespace variables;
    static GUIBurgerButton testIconButton(10.0, 10.0);
    if (testIconButton.isButtonToggled()) {
        drawCustomText("FATAL ERROR :(", Vector2{ 10, 10 }, labels, 1, RED);
    }
    else {
        drawCustomText("F SCENEZ :(", Vector2{ 10, 10 }, labels, 1, RED);
    }

    testIconButton.draw();
}