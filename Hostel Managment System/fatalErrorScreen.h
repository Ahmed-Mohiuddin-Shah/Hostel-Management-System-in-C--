#pragma once

void fatalErrorScreen() {
	using namespace variables;

	ErrorPopup errorPopup(1500.0f, 3.0f);

	while (!layerChangedHandler() && !WindowShouldClose())
	{
		// --------- Logic -----------------
		errorPopup.update();

		if (IsKeyPressed(KEY_SPACE)) {
			errorPopup.showMessage("We Stormin' the WHITE HOUSE with this one!!!!\n     Booiisss!!!");
		}

		// --------- Drawing GUI -----------
		BeginDrawing();
		ClearBackground(H_DARK_GREY);
		errorPopup.draw();
		guiOverlay();
		EndDrawing();
	}
}