#pragma once

void studentDetailsScreen() {
	using namespace variables;

	ErrorPopup errorPopup(1500.0f, 3.0f);

	while (!layerChangedHandler())
	{
		// --------- Logic -----------------
		errorPopup.update();

		// --------- Drawing GUI -----------
		BeginDrawing();
		ClearBackground(H_DARK_GREY);


		drawCustomBodyText("Student DEETS:", Vector2{ 0, 0 }, headings, 1, H_DARK_BLUE);

		drawCustomBodyText(hostelInstance.getAllStudentsTable().c_str(), Vector2{0, 115}, labels, 1, H_WHITE);

		errorPopup.draw();
		guiOverlay();
		EndDrawing();
	}
}