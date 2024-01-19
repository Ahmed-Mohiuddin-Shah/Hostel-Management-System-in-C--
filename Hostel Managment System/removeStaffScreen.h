#pragma once

#pragma once

void removeStaffScreen() {
	using namespace variables;

	ErrorPopup errorPopup(1500.0f, 3.0f);

	TextInputBox staffIDInputBox = { 90, 140, "Staff ID", true, 5 };
	GUIButton removeStaffButton = { 90, 190, "Remove Staff" };

	while (!layerChangedHandler())
	{
		// --------- Logic -----------------
		errorPopup.update();
		staffIDInputBox.update();

		if (removeStaffButton.isClicked()) {
			if (staffIDInputBox.getInputText().empty()) {
				errorPopup.showMessage("How Can You Remove A NOBODY!\n     Enter a Sombody's ID!!");
			}
			else {

				int staffID;

				try
				{
					staffID = std::stoi(staffIDInputBox.getInputText());
				}
				catch (const std::exception e)
				{
					fatalErrorMessage = e.what();
					currentLayer = FATAL_ERROR_SCREEN;
				}

				if (!hostelInstance.checkIfStaffExists(staffID)) {
					errorPopup.showMessage("Staff does not Exist!!!\n     Try A different ID!!");
				}
				else {
					hostelInstance.removeStaff(staffID);
					successPopupMessage = "Staff Removed Successfully!!";
					globalShouldShowSuccessPopup = true;
					currentLayer = STAFF_DETAILS_SCREEN;
				}
			}
		}

		// --------- Drawing GUI -----------
		BeginDrawing();
		ClearBackground(H_DARK_GREY);


		drawCustomBodyText("Remove Staff:", Vector2{ 0, 0 }, headings, 1, H_DARK_BLUE);
		staffIDInputBox.draw();
		removeStaffButton.draw();

		errorPopup.draw();
		guiOverlay();
		EndDrawing();
	}
}