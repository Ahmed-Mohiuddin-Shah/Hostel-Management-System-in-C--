#pragma once

void fatalErrorScreen() {
	using namespace variables;

	GUIButton testButton(20, 20, 150, 30, "Test Button");

	while (!WindowShouldClose())
	{
		// --------- Logic -----------------

		// --------- Drawing GUI -----------
		BeginDrawing();
		ClearBackground(H_DARK_GREY);
		if (testButton.isClicked()) {
			drawCustomText("FATAL ERROR :(", Vector2{ 10, 10 }, labels, 1, RED);
		}
		else {
			drawCustomText("F SCENEZ :(", Vector2{ 10, 10 }, labels, 1, RED);
		}
		
		testButton.draw();
		EndDrawing();
	}
}