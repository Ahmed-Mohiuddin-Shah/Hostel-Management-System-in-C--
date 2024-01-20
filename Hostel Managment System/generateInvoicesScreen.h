#pragma once

namespace addInvoiceFuncs {
	std::string validateInputs(TextInputBox* inputBoxes) {

		if (inputBoxes[0].getInputText().empty()) {
			return "Calculation Error!\n     Please provide the days in which invoice is due.";
		}

		if (inputBoxes[1].getInputText().empty()) {
			return "You running a charity over here?!\n     Enter a due amount!";
		}

		if (inputBoxes[2].getInputText().empty()) {
			return "What is life without fines!!\n     Provide some Fine!";
		}

		return "valid";
	}

	std::string getCurrentDateAsString()
	{
		// Get the current time
		std::time_t currentTime = std::time(nullptr);

		// Convert the current time to a struct tm
		std::tm* localTime = std::localtime(&currentTime);

		// Format the date as a string
		std::stringstream ss;
		ss << std::put_time(localTime, "%Y-%m-%d");
		return ss.str();
	}

	std::string addDaysToCurrentDate(int daysToAdd)
	{
		// Get the current time
		std::time_t currentTime = std::time(nullptr);

		// Convert the current time to a struct tm
		std::tm* date = std::localtime(&currentTime);

		// Add days to the date
		date->tm_mday += daysToAdd;
		std::mktime(date);

		// Format the updated date as a string
		std::stringstream result;
		result << std::put_time(date, "%Y-%m-%d");
		return result.str();
	}

}

void generateInvoicesScreen() {

	using namespace variables;
	GUIButton generateInvoice_s_Button(90, 390, "Add Invoice");

	const size_t numInputBoxes = 4;
	TextInputBox inputBoxes[numInputBoxes] = {
		{90, 140, "Due in how many days?", true, 11},
		{90, 190, "Amount Due", true, 10},
		{90, 240, "After Due Fine", true, 10},
		{90, 340, "StudentID", true, 11},
	};

	

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

		errorPopup.update();

		// --------- Drawing GUI -----------
		BeginDrawing();
		ClearBackground(H_DARK_GREY);
		drawCustomBodyText("Generate Invoice(s):", Vector2{ 0, 0 }, headings, 1, H_DARK_BLUE);
		drawCustomBodyText("Leave Empty To Generate For All Students", Vector2{ 0, 300 }, labels, 1, RED);
		generateInvoice_s_Button.draw();

		// Draw the input boxes
		for (size_t i = 0; i < numInputBoxes; ++i) {
			inputBoxes[i].draw();
		}


		if (generateInvoice_s_Button.isClicked()) {

			std::string validityMessage = addInvoiceFuncs::validateInputs(inputBoxes);
			if (validityMessage == "valid") {

				int dueDays;
				int dueAmount;
				int afterDueAmount;
				int studentID;

				try
				{
					dueDays = std::stoi(inputBoxes[0].getInputText());
					dueAmount = std::stoi(inputBoxes[1].getInputText());
					afterDueAmount = std::stoi(inputBoxes[2].getInputText());
					studentID = std::stoi(inputBoxes[3].getInputText());
				}
				catch (const std::exception e)
				{
					fatalErrorMessage = e.what();
					currentLayer = FATAL_ERROR_SCREEN;
				}

				if (!inputBoxes[3].getInputText().empty()) {
					if (!hostelInstance.checkIfStudentExists(studentID)) {
						errorPopup.showMessage("Student ID does not Exist!!!\n     Try A different ID!!");
					}
					else {
						hostelInstance.addInvoice(studentID, addInvoiceFuncs::getCurrentDateAsString(), addInvoiceFuncs::addDaysToCurrentDate(dueDays), dueAmount, dueAmount + afterDueAmount);
						successPopupMessage = "Invoice Added Successfully!!";
						globalShouldShowSuccessPopup = true;
						currentLayer = DISPLAY_INVOICES_SCREEN;
					}
				}
				else {
					hostelInstance.addInvoicesForAllStudents(addInvoiceFuncs::getCurrentDateAsString(), addInvoiceFuncs::addDaysToCurrentDate(dueDays), dueAmount, dueAmount + afterDueAmount);
					successPopupMessage = "Invoices Added Successfully!!";
					globalShouldShowSuccessPopup = true;
					currentLayer = DISPLAY_INVOICES_SCREEN;
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