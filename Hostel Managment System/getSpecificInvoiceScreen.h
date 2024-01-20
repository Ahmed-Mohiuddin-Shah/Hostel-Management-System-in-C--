#pragma once

void getSpecificInvoiceScreen()
{
	using namespace variables;
	GUIButton filterInvoicesButton(90, 290, "Filter Invoices");

	const size_t numInputBoxes = 2;
	TextInputBox inputBoxes[numInputBoxes] = {
		{90, 140, "Invoice ID", true, 10},
		{90, 190, "StudentID", true, 11}
	};

	GUIToggleButton statusToggleButton = { 90, 240, "Paid", "UnPaid", "Invoice Status: " };

	bool anySelected = false;

	ErrorPopup errorPopup(1500.0f, 2.0f);

	std::string invoicesTable = hostelInstance.getAllInvoicesTable();

	GUIScrollView scrollView = { 90, 350, invoicesTable };

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

		statusToggleButton.update();
		scrollView.update();
		errorPopup.update();

		// --------- Drawing GUI -----------
		BeginDrawing();
		ClearBackground(H_DARK_GREY);

		scrollView.draw();


		DrawRectangle(0, 0, screenWidth, 270, H_DARK_GREY);
		DrawRectangleGradientV(0, 270, screenWidth, 330, H_DARK_GREY, BLANK);

		drawCustomBodyText("Invoices:", Vector2{ 0, 0 }, headings, 1, H_DARK_BLUE);
		filterInvoicesButton.draw();
		statusToggleButton.draw();


		// Draw the input boxes
		for (size_t i = 0; i < numInputBoxes; ++i) {
			inputBoxes[i].draw();
		}

		if (filterInvoicesButton.isClicked()) {
			if (!inputBoxes[0].getInputText().empty()) {
				int invoiceID;

				try
				{
					invoiceID = std::stoi(inputBoxes[0].getInputText());
				}
				catch (const std::exception e)
				{
					fatalErrorMessage = e.what();
					currentLayer = FATAL_ERROR_SCREEN;
				}
				invoicesTable = hostelInstance.getAllInvoicesByInvoiceID(invoiceID);
			}
			else if (!inputBoxes[1].getInputText().empty()) {
				int studentID;

				try
				{
					studentID = std::stoi(inputBoxes[1].getInputText());
				}
				catch (const std::exception e)
				{
					fatalErrorMessage = e.what();
					currentLayer = FATAL_ERROR_SCREEN;
				}
				invoicesTable = hostelInstance.getAllInvoicesByStudentID(studentID, statusToggleButton.getState());
			}
			else {
				invoicesTable = hostelInstance.getAllInvoicesByStatus(statusToggleButton.getState());
			}

			scrollView.setText(invoicesTable);
		}



		errorPopup.draw();
		guiOverlay();
		EndDrawing();
	}
}