#pragma once

// -------------- Overlay ------------------------
void guiOverlay() {
    using namespace variables;
    static GUIBurgerButton burgerButton(10, 10);
    static GUISidebar sideBar(300);

    // Update
    sideBar.shouldShow(burgerButton.isButtonToggled());


    // GUI
    
    sideBar.draw();
    burgerButton.draw();

    if (burgerButton.isButtonToggled()) {
        animateBugCatGIF(burgerMenuBugCatPosition);
    }
}