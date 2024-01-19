#pragma once

void addRoomScreen() {
	using namespace variables;

	ErrorPopup errorPopup(1500.0f, 3.0f);

	TextInputBox roomNumberInputBox = { 90, 140, "Room Number", true, 5 };
	GUIButton addRoomButton = { 90, 190, "Add Room" };

	while (!layerChangedHandler())
	{
		// --------- Logic -----------------
		errorPopup.update();
		roomNumberInputBox.update();

		if (addRoomButton.isClicked()) {
			
			int roomNumber;

			try
			{
				roomNumber = std::stoi(roomNumberInputBox.getInputText());
			}
			catch (const std::exception e)
			{
				fatalErrorMessage = e.what();
				currentLayer = FATAL_ERROR_SCREEN;
			}

			if (hostelInstance.roomNumberExists(roomNumber)) {
				errorPopup.showMessage("Room Already Exists!!!\n     Try A different Number!!");
			}
			else {
				hostelInstance.addRoom(roomNumber);
				successPopupMessage = "Room Added Successfully!!";
				globalShouldShowSuccessPopup = true;
				currentLayer = ROOM_DETAILS_SCREEN;
			}
		}

		// --------- Drawing GUI -----------
		BeginDrawing();
		ClearBackground(H_DARK_GREY);
		errorPopup.draw();

		drawCustomBodyText("Add Room:", Vector2{ 0, 0 }, headings, 1, H_DARK_BLUE);
		roomNumberInputBox.draw();
		addRoomButton.draw();


		guiOverlay();
		EndDrawing();
	}
}