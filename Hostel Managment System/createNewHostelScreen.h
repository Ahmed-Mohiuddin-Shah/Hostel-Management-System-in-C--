#pragma once

void createNewHostelScreen() {
	using namespace variables;

	GUIButton createHostelButton(screenWidth / 2 - (widthPerCharacterForLabels * 18) / 2, 530, widthPerCharacterForLabels * 18, labelsTextHeight, "Create new Hostel!"); // widthPerCharacterForLabels * (X) ; here X is number of characters
	GUIButton exitProgramButton(screenWidth / 2 - (widthPerCharacterForLabels * 4) / 2, 580, widthPerCharacterForLabels * 4, labelsTextHeight, "Exit");

	while (!WindowShouldClose())
	{
		// --------- Logic -----------------


		// TODO change shouldExit to exit screen
		if (exitProgramButton.isClicked()) {
			shouldExit = true;
			break;
		}

		// --------- Drawing GUI -----------
		BeginDrawing();
		ClearBackground(H_DARK_GREY);
		createHostelButton.draw();
		exitProgramButton.draw();
		EndDrawing();
	}
}