/*


		folly::dynamic studentsArray = folly::dynamic::array;

		for (int i = 1; i <= 10; i++) {
			folly::dynamic studentData = folly::dynamic::object;
			studentData["s_id"] = i;
			studentData["s_name"] = "TestName";
			studentData["s_age"] = 18 + i;
			studentData["s_gender"] = i%2?"male":"female";
			studentsArray.push_back(studentData);
		}

		parsedJson["students"] = studentsArray;

*/



// --------- Logic -----------------
// --------- Drawing GUI -----------

/*
* 
* Basic Screen Boiler Plate

	using namespace variables;

	ErrorPopup errorPopup(1500.0f, 3.0f);

	while (!layerChangedHandler())
	{
		// --------- Logic -----------------
		errorPopup.update();

		// --------- Drawing GUI -----------
		BeginDrawing();
		ClearBackground(H_DARK_GREY);

		drawCustomBodyText("Fatal Error \n\n\n\n\n\nOccured!!!", Vector2{ 0, 0 }, variables::headings, 1, RED);
		drawCustomBodyText(fatalErrorMessage.c_str(), Vector2{ 0, 230 }, variables::labels, 1, RED);
		DrawTexture(fatalErrorTexture, screenWidth - fatalErrorTexture.width, screenHeight - fatalErrorTexture.height, WHITE);

		errorPopup.draw();
		guiOverlay();
		EndDrawing();
	}

*/