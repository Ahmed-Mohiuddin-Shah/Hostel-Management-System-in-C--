#pragma once

void promoteStudentsScreen() {
	using namespace variables;

	ErrorPopup errorPopup(1500.0f, 3.0f);

	TextInputBox promoteInputBox = { 90, 140, "Write \"Promote\" Then Click Confirm ", false, 7 };
	GUIButton promoteButton = { 90, 190, "Confirm" };

	while (!layerChangedHandler())
	{
		// --------- Logic -----------------
		errorPopup.update();
		promoteInputBox.update();

		if (promoteButton.isClicked()) {
			if (promoteInputBox.getInputText().empty()) {
				errorPopup.showMessage("Write \"Promote\" to Promote Everyone!!");
			}
			else if (promoteInputBox.getInputText() != "Promote") {
				errorPopup.showMessage("You Need to write \"Promote\" to Promote Everyone!!");
			}
			else {
				
				hostelInstance.promoteAllStudents();
				successPopupMessage = "Students Promoted Successfully!!";
				globalShouldShowSuccessPopup = true;
				currentLayer = STUDENT_DETAILS_SCREEN;
			}
		}

		// --------- Drawing GUI -----------
		BeginDrawing();
		ClearBackground(H_DARK_GREY);


		drawCustomBodyText("Promote Students:", Vector2{ 0, 0 }, headings, 1, H_DARK_BLUE);
		promoteInputBox.draw();
		promoteButton.draw();

		errorPopup.draw();
		guiOverlay();
		EndDrawing();
	}
}