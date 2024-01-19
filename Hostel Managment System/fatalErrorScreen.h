#pragma once

void fatalErrorScreen() {
	using namespace variables;

	ErrorPopup errorPopup(1500.0f, 3.0f);
	errorPopup.showMessage(errorPopupMessage);

	while (!layerChangedHandler() && !WindowShouldClose())
	{
		// --------- Logic -----------------
		errorPopup.update();

		// --------- Drawing GUI -----------
		BeginDrawing();
		ClearBackground(H_DARK_GREY);
		errorPopup.draw();

		drawCustomBodyText("Fatal Error \n\n\n\n\nOccured!!!", Vector2{0, 0}, variables::headings, 1, RED);
		DrawTexture(fatalErrorTexture, screenWidth - fatalErrorTexture.width, screenHeight - fatalErrorTexture.height, WHITE);

		guiOverlay();
		EndDrawing();
	}
}