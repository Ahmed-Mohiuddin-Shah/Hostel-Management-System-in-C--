#pragma once

namespace addStaffFuncs {
	std::string validateInputs(TextInputBox* inputBoxes) {

		if (inputBoxes[0].getInputText().empty()) {
			return "Error 404: ID not found!\n     Please provide a valid staff ID.";
		}

		if (inputBoxes[1].getInputText().empty()) {
			return "Error: Staff needs a name!\n     Did you hire a ghost?";
		}

		if (inputBoxes[2].getInputText().empty()) {
			return "Uh-oh! Looks like our staff is too shy to reveal their CNIC.\n     Please share it with us!";
		}

		if (inputBoxes[3].getInputText().empty()) {
			return "Error: Missing contact info! Our staff might be avoiding telemarketers.\n     Help us reach them!";
		}

		if (inputBoxes[4].getInputText().empty()) {
			return "Error: Staff without a role is like a ship without\n     a captain. Specify a role, please!";
		}

		return "valid";
	}
}

void addStaffScreen() {

	using namespace variables;
	GUIButton addStaffButton(90, 390, "Add Staff");

	const size_t numInputBoxes = 5;
	TextInputBox inputBoxes[numInputBoxes] = {
		{90, 140, "ID", true, 11},
		{90, 190, "Name", false, 64},
		{90, 240, "CNIC", true, 13},
		{90, 290, "Phone Number", true, 11},
		{90, 340, "Role", false, 30}
	};

	bool anySelected = false;

	ErrorPopup errorPopup(1500.0f, 2.0f);

	while (!layerChangedHandler() && !shouldExit)
	{
		// --------- Logic -----------------
		// Update input boxes
		for (size_t i = 0; i < numInputBoxes; ++i) {
			inputBoxes[i].update();
		}

		// Deselect other input boxes when one is clicked
		for (size_t i = 0; i < numInputBoxes; ++i) {
			if (inputBoxes[i].isActive()) {
				anySelected = true;
				break;
			}
		}

		if (anySelected) {
			for (size_t i = 0; i < numInputBoxes; ++i) {
				if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(GetMousePosition(), inputBoxes[i].getBounds())) {
					// If a new input box is clicked, deactivate others
					for (size_t j = 0; j < numInputBoxes; ++j) {
						if (i != j) {
							inputBoxes[j].deSelect();
						}
					}
					break;
				}
			}
		}

		errorPopup.update();

		// --------- Drawing GUI -----------
		BeginDrawing();
		ClearBackground(H_DARK_GREY);
		drawCustomBodyText("Add Staff:", Vector2{ 0, 0 }, headings, 1, H_DARK_BLUE);
		addStaffButton.draw();

		// Draw the input boxes
		for (size_t i = 0; i < numInputBoxes; ++i) {
			inputBoxes[i].draw();
		}

		if (addStaffButton.isClicked()) {

			std::string validityMessage = addStaffFuncs::validateInputs(inputBoxes);
			if (validityMessage == "valid") {

				int staffID;

				try
				{
					staffID = std::stoi(inputBoxes[0].getInputText());
				}
				catch (const std::exception e)
				{
					fatalErrorMessage = e.what();
					currentLayer = FATAL_ERROR_SCREEN;
				}

				if (hostelInstance.checkIfStaffExists(staffID)) {
					errorPopup.showMessage("Staff ID Already Exists!!!\n     Try A different ID!!");
				}
				else {
					hostelInstance.addStaff(staffID, inputBoxes[1].getInputText(), inputBoxes[2].getInputText(), inputBoxes[3].getInputText(), inputBoxes[4].getInputText());
					successPopupMessage = "Staff Added Successfully!!";
					globalShouldShowSuccessPopup = true;
					currentLayer = STAFF_DETAILS_SCREEN;
				}
			}
			else {
				errorPopup.showMessage(validityMessage);
			}
		}

		errorPopup.draw();
		guiOverlay();
		EndDrawing();
	}

}