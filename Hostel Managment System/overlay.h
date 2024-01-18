#pragma once

// -------------- Overlay ------------------------
void guiOverlay() {
    using namespace variables;
    static GUIBurgerButton burgerButton(10, 10);
    static GUISidebar sideBar(400);

    // Update
    sideBar.shouldShowUpdate(burgerButton.isButtonToggled());


    // GUI
    
    sideBar.draw();
    burgerButton.draw();
}