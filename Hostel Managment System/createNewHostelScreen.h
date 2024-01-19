#pragma once

std::string validateInputs(TextInputBox *inputBoxes) {

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

bool saveHostelInfo(TextInputBox* inputBoxes) {
	JSON hostelInfoJson;
	hostelInfoJson["hostel_name"] = inputBoxes[0].getInputText();
	hostelInfoJson["hostel_address"] = inputBoxes[1].getInputText();
	hostelInfoJson["hostel_ph_no"] = inputBoxes[2].getInputText();
	hostelInfoJson["hostel_email"] = inputBoxes[3].getInputText();

	std::string hostelInfoJsonString = hostelInfoJson.dump();

	try
	{
		FileReader::createFile(ProjectInfo::fileName);
		FileReader::writeToFile(ProjectInfo::fileName, hostelInfoJsonString);
	}
	catch (const std::exception&)
	{
		FileReader::deleteFile(ProjectInfo::fileName);
		return false;
	}

	variables::currentLayer = variables::FATAL_ERROR_SCREEN;

	return true;
}

void createNewHostelScreen() {
	using namespace variables;
	GUIButton createHostelButton(15, screenHeight - 2*(labelsTextHeight + 20), "Create new Hostel!"); // widthPerCharacterForLabels * (X) ; here X is number of characters
	GUIButton exitProgramButton(15, screenHeight - labelsTextHeight - 10,  "Exit");

	const size_t numInputBoxes = 4;
	TextInputBox inputBoxes[numInputBoxes] = {
		{15, 200, "Hostel Name", false},
		{15, 300, "Hostel Address", false},
		{15, 400, "Hostel Phone Number", true},
		{15, 500, "Hostel Email", false}
	};

	bool anySelected = false;

	ErrorPopup errorPopup(1500.0f, 2.0f);

	while (!layerChangedHandler() && !WindowShouldClose())
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
			shouldExit = true;
			break;
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
			std::string validityMessage = validateInputs(inputBoxes);
			if (validityMessage == "valid") {
				if (!saveHostelInfo(inputBoxes)) {
					errorPopup.showMessage("Failed to save Info!!\n     Try agiain UwU!!");
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
	successPopupMessage = "Hostel File Created Successfully";

}