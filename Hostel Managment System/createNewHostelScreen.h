#pragma once

void createNewHostelScreen() {
	using namespace variables;

	GUIButton createHostelButton(screenWidth / 2 - (widthPerCharacterForLabels * 18) / 2, 530, "Create new Hostel!"); // widthPerCharacterForLabels * (X) ; here X is number of characters
	GUIButton exitProgramButton(screenWidth / 2 - (widthPerCharacterForLabels * 4) / 2, 580,  "Exit");

	TextInputBox myTextInputBox(100, 100, "Enter text");

	while (!WindowShouldClose())
	{
		// --------- Logic -----------------

		myTextInputBox.update();

		// TODO change shouldExit to exit screen
		if (exitProgramButton.isClicked()) {
			shouldExit = true;
			break;
		}

		// --------- Drawing GUI -----------
		BeginDrawing();
		ClearBackground(H_DARK_GREY);
		drawCustomText("New Hostel DEETS", Vector2{ screenWidth / 2 - (widthPerCharacterForHeadings * 16) / 2, 10 }, headings, 1, H_WHITE);
		createHostelButton.draw();
		exitProgramButton.draw();
		myTextInputBox.draw();
		EndDrawing();
	}
}