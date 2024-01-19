#pragma once

// -------------- Overlay ------------------------
void guiOverlay() {
    using namespace variables;

    static GUIBurgerButton burgerButton(10, 10);
    static GUISidebar sideBar(400);
    static SuccessPopup successPopup(1500.0f, 3.0f);

    // Update
    successPopup.update();
    burgerButton.setButtonToggled(globalBurgerButtonToggleState);

    sideBar.shouldShowUpdate(burgerButton.isButtonToggled());
    sideBar.checkToChangeLayer();
    if (sideBar.isMouseClickedOutsideOfSideBar()) {
        globalBurgerButtonToggleState = false;
    }

    if (variables::globalShouldShowSuccessPopup) {
        successPopup.showMessage(variables::successPopupMessage);
        variables::globalShouldShowSuccessPopup = false;
    }


    // GUI
    sideBar.draw();
    burgerButton.draw();
    successPopup.draw();
}