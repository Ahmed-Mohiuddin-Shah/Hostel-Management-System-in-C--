#pragma once

bool validateInputs(TextInputBox *inputBoxes) {

	if (inputBoxes[0].getInputText().empty() || inputBoxes[1].getInputText().empty() || inputBoxes[2].getInputText().empty() || inputBoxes[3].getInputText().empty()) {
		return false;
	}
	return true;
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

		// TODO change shouldExit to exit screen
		if (exitProgramButton.isClicked()) {
			shouldExit = true;
			break;
		}
		if (createHostelButton.isClicked()) {
			if (validateInputs(inputBoxes)) {
				saveHostelInfo(inputBoxes);
			}
			else {
				std::cout << "Invalid Input" << std::endl;
			}
		}

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

		EndDrawing();
	}
}