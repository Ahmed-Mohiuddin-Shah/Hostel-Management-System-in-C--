#pragma once

void staffDetailsScreen() {
	using namespace variables;

	ErrorPopup errorPopup(1500.0f, 3.0f);

	GUIScrollView scrollView = { 90, 140, hostelInstance.getAllStaffsTable() };

	while (!layerChangedHandler())
	{
		// --------- Logic -----------------
		errorPopup.update();
		scrollView.update();

		// --------- Drawing GUI -----------
		BeginDrawing();
		ClearBackground(H_DARK_GREY);

		scrollView.draw();

		DrawRectangle(0, 0, screenWidth, 80, H_DARK_GREY);
		DrawRectangleGradientV(0, 80, screenWidth, 140, H_DARK_GREY, BLANK);

		drawCustomBodyText("Staff DEETS:", Vector2{ 0, 0 }, headings, 1, H_DARK_BLUE);

		errorPopup.draw();
		guiOverlay();
		EndDrawing();
	}
}