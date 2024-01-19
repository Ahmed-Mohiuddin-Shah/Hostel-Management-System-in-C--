#pragma once

void hostelDetailsScreen() {
	using namespace variables;

	std::string hostelName = hostelJSON["hostel_name"].template get<std::string>();
	std::string hostelAddress = hostelJSON["hostel_address"].template get<std::string>();
	std::string hostelPhNo = hostelJSON["hostel_ph_no"].template get<std::string>();
	std::string hostelEmail = hostelJSON["hostel_email"].template get<std::string>();

	while (!layerChangedHandler())
	{
		// --------- Logic -----------------

		// --------- Drawing GUI -----------
		BeginDrawing();
		ClearBackground(H_DARK_GREY);
		drawCustomBodyText("Hostel DEETS:", Vector2{ 0, 0 }, variables::headings, 1, WHITE);
		drawCustomBodyText(TextFormat("Hostel Name          : %s", hostelName.c_str()), Vector2{0, 140}, variables::labels, 1, variables::H_BLUE);
		drawCustomBodyText(TextFormat("Hostel Address       : %s", hostelAddress.c_str()), Vector2{ 0, 170 }, variables::labels, 1, variables::H_BLUE);
		drawCustomBodyText(TextFormat("Hostel Phone Number  : %s", hostelPhNo.c_str()), Vector2{ 0, 200 }, variables::labels, 1, variables::H_BLUE);
		drawCustomBodyText(TextFormat("Hostel Email         : %s", hostelEmail.c_str()), Vector2{ 0, 230 }, variables::labels, 1, variables::H_BLUE);
		guiOverlay();
		EndDrawing();
	}
}