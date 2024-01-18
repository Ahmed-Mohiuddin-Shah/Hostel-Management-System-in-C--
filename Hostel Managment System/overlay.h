#pragma once

// -------------- Overlay ------------------------
void guiOverlay() {
    using namespace variables;

    static GUIBurgerButton burgerButton(10, 10);
    static GUISidebar sideBar(400);

    // Update

    burgerButton.setButtonToggled(globalBurgerButtonToggleState);

    sideBar.shouldShowUpdate(burgerButton.isButtonToggled());
    sideBar.checkToChangeLayer();


    // GUI
    
    sideBar.draw();
    burgerButton.draw();
}