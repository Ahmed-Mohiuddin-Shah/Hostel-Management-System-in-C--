#pragma once

void fatalErrorScreen() {
	using namespace variables;

	SuccessPopup errorPopup(1000.0f, 3.0f);

	while (!layerChangedHandler() && !WindowShouldClose())
	{
		// --------- Logic -----------------
		errorPopup.update();

		if (IsKeyPressed(KEY_SPACE)) {
			errorPopup.showMessage("Error: We Stormin' the WHITE HOUSE with this one!!!!");
		}

		// --------- Drawing GUI -----------
		BeginDrawing();
		ClearBackground(H_DARK_GREY);
		errorPopup.draw();
		guiOverlay();
		EndDrawing();
	}
}