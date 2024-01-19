#pragma once

void addStudentScreen() {
	using namespace variables;

	ErrorPopup errorPopup(1500.0f, 3.0f);

	while (!layerChangedHandler())
	{
		// --------- Logic -----------------
		errorPopup.update();

		// --------- Drawing GUI -----------
		BeginDrawing();
		ClearBackground(H_DARK_GREY);
		errorPopup.draw();

		drawCustomBodyText(hostelInstance.getAllStudentsTable().c_str(), { 0, 0 }, labels, 1, H_WHITE);

		guiOverlay();
		EndDrawing();
	}
}