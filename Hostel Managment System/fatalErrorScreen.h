#pragma once

void fatalErrorScreen() {
	using namespace variables;

	while (!WindowShouldClose())
	{
		// --------- Logic -----------------

		// --------- Drawing GUI -----------
		BeginDrawing();
		ClearBackground(H_DARK_GREY);

		guiOverlay();
		EndDrawing();
	}
}