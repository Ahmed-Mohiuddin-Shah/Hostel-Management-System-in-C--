#pragma once

namespace createHostelFuncs {
	std::string validateInputs(TextInputBox* inputBoxes) {

		if (inputBoxes[0].getInputText().empty()) {
			return "Error 404: Hostel Name Not Found!\n     Did it run away?";
		}

		if (inputBoxes[1].getInputText().empty()) {
			return "Hold on, we're searching the universe\n     for a Hostel without an address...";
		}

		if (inputBoxes[2].getInputText().empty()) {
			return "Hostel Phone Number missing.\n     Are you sure it's not on airplane mode?";
		}

		if (inputBoxes[3].getInputText().empty()) {
			return "Hostel Email not provided.\n     Did you forget to send it an invitation?";
		}
		return "valid";
	}

	std::string saveHostelInfo(TextInputBox* inputBoxes) {
		JSON hostelInfoJson;
		hostelInfoJson["hostel_name"] = inputBoxes[0].getInputText();
		hostelInfoJson["hostel_address"] = inputBoxes[1].getInputText();
		hostelInfoJson["hostel_ph_no"] = inputBoxes[2].getInputText();
		hostelInfoJson["hostel_email"] = inputBoxes[3].getInputText();
		hostelInfoJson["inv_id_track"] = 0;
		hostelInfoJson["mode"] = true;
		hostelInfoJson["students"] = {};
		hostelInfoJson["staffs"] = {};
		hostelInfoJson["rooms"] = {};
		hostelInfoJson["invoices"] = {};

		std::string hostelInfoJsonString = hostelInfoJson.dump(4);

		try
		{
			FileReader::createFile(ProjectInfo::fileName);
			FileReader::writeToFile(ProjectInfo::fileName, hostelInfoJsonString);
		}
		catch (const std::exception e)
		{
			FileReader::deleteFile(ProjectInfo::fileName);
			return e.what();
		}

		variables::currentLayer = variables::LOADING_SCREEN;

		return "saved";
	}
}

void createNewHostelScreen() {

	using namespace variables;
	GUIButton createHostelButton(15, screenHeight - 2*(labelsTextHeight + 20), "Create new Hostel!"); // widthPerCharacterForLabels * (X) ; here X is number of characters
	GUIButton exitProgramButton(15, screenHeight - labelsTextHeight - 10,  "Exit");

	const size_t numInputBoxes = 4;
	TextInputBox inputBoxes[numInputBoxes] = {
		{15, 200, "Hostel Name", false, 64},
		{15, 300, "Hostel Address", false, 64},
		{15, 400, "Hostel Phone Number", true, 11},
		{15, 500, "Hostel Email", false, 64}
	};

	bool anySelected = false;

	ErrorPopup errorPopup(1500.0f, 2.0f);
	errorPopup.showMessage("Hostel Info Not Found!!\n     Please Enter New Info!!");

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

		if (exitProgramButton.isClicked()) {
			// This Should Not Go Through ExitScreen But
			// Should Directly Exit The Program
			shouldExit = true;
		}

		errorPopup.update();

		// --------- Drawing GUI -----------
		BeginDrawing();
		ClearBackground(H_DARK_GREY);
		drawCustomText("New Hostel DEETS", Vector2{ 15, 10 }, headings, 1, H_WHITE);
		createHostelButton.draw();
		exitProgramButton.draw();

		// Draw the input boxes
		for (size_t i = 0; i < numInputBoxes; ++i) {
			inputBoxes[i].draw();
		}

		if (createHostelButton.isClicked()) {
			std::string validityMessage = createHostelFuncs::validateInputs(inputBoxes);
			if (validityMessage == "valid") {
				validityMessage = createHostelFuncs::saveHostelInfo(inputBoxes);
				if (validityMessage != "saved") {
					errorPopup.showMessage(validityMessage);
				}
			}
			else {
				errorPopup.showMessage(validityMessage);
			}
		}

		errorPopup.draw();

		EndDrawing();
	}

	globalShouldShowSuccessPopup = true;
	variables::successPopupMessage = "Hostel File Created!\n     Even the tech gremlins gave it a thumbs up.";

}