#pragma once

void homeScreen() {
	using namespace variables;

	if (hostelInstance.getHostelName() == "") {
		currentLayer = CREATE_NEW_HOSTEL_SCREEN;
		return;
	}

	while (!layerChangedHandler())
	{
		// --------- Logic -----------------

		// --------- Drawing GUI -----------
		BeginDrawing();
		ClearBackground(H_DARK_GREY);
		drawCustomBodyText("Welcome To:", Vector2{ 0, 0 }, variables::headings, 1, WHITE);
		drawCustomBodyText(hostelJSON["hostel_name"].template get<std::string>().c_str(), Vector2{0, 140}, variables::headings, 1, variables::H_BLUE);
		guiOverlay();
		EndDrawing();
	}
}