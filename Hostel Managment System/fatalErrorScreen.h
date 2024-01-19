#pragma once

void fatalErrorScreen() {
	using namespace variables;

	ErrorPopup errorPopup(1500.0f, 3.0f);
	errorPopup.showMessage("Fatal Error Occured!!!");

	while (!layerChangedHandler())
	{
		// --------- Logic -----------------
		errorPopup.update();

		// --------- Drawing GUI -----------
		BeginDrawing();
		ClearBackground(H_DARK_GREY);


		drawCustomBodyText("Fatal Error \n\n\n\n\n\nOccured!!!", Vector2{0, 0}, variables::headings, 1, RED);
		drawCustomBodyText(fatalErrorMessage.c_str(), Vector2{0, 230}, variables::labels, 1, RED);
		DrawTexture(fatalErrorTexture, screenWidth - fatalErrorTexture.width, screenHeight - fatalErrorTexture.height, WHITE);

		errorPopup.draw();
		guiOverlay();
		EndDrawing();
	}
}