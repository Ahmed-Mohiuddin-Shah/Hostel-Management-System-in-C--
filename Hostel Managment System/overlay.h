#pragma once

// -------------- Overlay ------------------------
void guiOverlay() {
    using namespace variables;
    static GUIBurgerButton burgerButton(10, 10);

    if (burgerButton.isButtonToggled()) {
        animateBugCatGIF(burgerMenuBugCatPosition);
    }

    burgerButton.draw();
}