#pragma once

namespace addStudentFuncs {
	std::string validateInputs(TextInputBox* inputBoxes) {

		if (inputBoxes[0].getInputText().empty()) {
			return "Error 404: ID not found!\n     Please provide a valid student ID.";
		}

		if (inputBoxes[1].getInputText().empty()) {
			return "Error: Student needs a name!\n     Are they a ghost?";
		}

		if (inputBoxes[2].getInputText().empty()) {
			return "Iz Student Illegal Imigrant?!!\n      Provide ze CNIC!!";
		}

		if (inputBoxes[3].getInputText().empty()) {
			return "Error: Missing phone number info!\n     How will we contact Student!";
		}

		if (inputBoxes[4].getInputText().empty()) {
			return "How are you student without a school?\n     Specify your scool!!";
		}


		if (inputBoxes[5].getInputText().empty()) {
			return "You forgot what semester you're in??\n     Try to remember!!";
		}

		if (inputBoxes[6].getInputText().empty()) {
			return "How are you going to stay without a room\n     Specify a room number!!";
		}

		return "valid";
	}
}

void addStudentScreen() {

	using namespace variables;
	GUIButton addStudentButton(90, 540, "Add Student");
	GUIButton deleteStudentButton(310, 140, "Delete Student");

	const size_t numInputBoxes = 7;
	TextInputBox inputBoxes[numInputBoxes] = {
		{90, 140, "ID", true, 11},
		{90, 190, "Name", false, 64},
		{90, 240, "CNIC", true, 13},
		{90, 290, "Phone Number", true, 11},
		{90, 340, "School", false, 30},
		{90, 440, "Semester", true, 1},
		{90, 490, "Room Number", true, 5}
	};

	GUIToggleButton genderToggleButton = { 90, 390, "Male", "Female", "Gender: " };

	bool anySelected = false;

	ErrorPopup errorPopup(1500.0f, 2.0f);

	if (!hostelInstance.areRoomsAvailable()) {
		currentLayer = ADD_ROOM_SCREEN;
		globalShouldShowRoomNotAvailableErrorPopup = true;
	}

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

		genderToggleButton.update();

		errorPopup.update();

		// --------- Drawing GUI -----------
		BeginDrawing();
		ClearBackground(H_DARK_GREY);
		drawCustomBodyText("Add/Delete Student:", Vector2{ 0, 0 }, headings, 1, H_DARK_BLUE);
		addStudentButton.draw();

		deleteStudentButton.draw();
		drawCustomBodyText("Only Need Student ID to delete Student!", Vector2{ 410, 140 }, labels, 1, RED);

		// Draw the input boxes
		for (size_t i = 0; i < numInputBoxes; ++i) {
			inputBoxes[i].draw();
		}

		genderToggleButton.draw();

		if (deleteStudentButton.isClicked()) {
			if (inputBoxes[0].getInputText().empty()) {
				errorPopup.showMessage("You Need An ID to Delete Student!!");
			}
			else {
				int studentID;

				try
				{
					studentID = std::stoi(inputBoxes[0].getInputText());
				}
				catch (const std::exception e)
				{
					fatalErrorMessage = e.what();
					currentLayer = FATAL_ERROR_SCREEN;
				}

				if (!hostelInstance.checkIfStudentExists(studentID)) {
					errorPopup.showMessage("Student Does Not Exist!!\     Try a different ID");
				}
				else {
					hostelInstance.deleteStudent(studentID);
					successPopupMessage = "Student removed Successfully!!";
					globalShouldShowSuccessPopup = true;
					currentLayer = STUDENT_DETAILS_SCREEN;
				}
			}
		}

		if (addStudentButton.isClicked()) {

			std::string validityMessage = addStudentFuncs::validateInputs(inputBoxes);
			if (validityMessage == "valid") {

				int studentID;
				int semester;
				int roomNumber;

				try
				{
					studentID = std::stoi(inputBoxes[0].getInputText());
					semester = std::stoi(inputBoxes[5].getInputText());
					roomNumber = std::stoi(inputBoxes[6].getInputText());
				}
				catch (const std::exception e)
				{
					fatalErrorMessage = e.what();
					currentLayer = FATAL_ERROR_SCREEN;
				}

				if (hostelInstance.checkIfStudentExists(studentID)) {
					errorPopup.showMessage("Student ID Already Exists!!!\n     Try A different ID!!");
				}
				else if (!hostelInstance.roomExists(roomNumber)) {
					errorPopup.showMessage("Room Does not Exist!!");
				}
				else if (!hostelInstance.isRoomSpaceAvailable(roomNumber)){
					errorPopup.showMessage("Room not Empty!!");
				}
				else {
					hostelInstance.addStudent(studentID, inputBoxes[1].getInputText(), inputBoxes[2].getInputText(), inputBoxes[3].getInputText(), inputBoxes[4].getInputText(), genderToggleButton.getValue(), semester, roomNumber);
					successPopupMessage = "Student Added Successfully!!";
					globalShouldShowSuccessPopup = true;
					currentLayer = STUDENT_DETAILS_SCREEN;
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