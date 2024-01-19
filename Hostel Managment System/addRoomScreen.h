#pragma once

void addRoomScreen() {
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

		drawCustomBodyText("Add Room:", Vector2{ 0, 0 }, headings, 1, H_DARK_BLUE);

		guiOverlay();
		EndDrawing();
	}
}