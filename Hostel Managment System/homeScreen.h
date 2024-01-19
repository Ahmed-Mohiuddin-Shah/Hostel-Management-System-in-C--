#pragma once

void homeScreen() {
	using namespace variables;

	while (!layerChangedHandler() && !WindowShouldClose())
	{
		// --------- Logic -----------------

		// --------- Drawing GUI -----------
		BeginDrawing();
		ClearBackground(H_DARK_GREY);
		drawCustomText("Welcome To:", Vector2{ 10, 40 }, variables::headings, 1, WHITE);
		drawCustomText(hostelJSON["hostel_name"].template get<std::string>().c_str(), Vector2{10, 195}, variables::headings, 1, variables::H_BLUE);
		guiOverlay();
		EndDrawing();
	}
}