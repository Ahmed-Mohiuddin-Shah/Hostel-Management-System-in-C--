#pragma once

variables::FileLoadStatus loadHostelDB() {

	std::this_thread::sleep_for(std::chrono::seconds(5));  // HEHE Delay for Funsies :)

	using namespace variables;
	if (!FileReader::checkIfFileExists(ProjectInfo::fileName)) {
		return DOES_NOT_EXIST;
	}
	try
	{
		fileContent = FileReader::readFromFile(ProjectInfo::fileName);
		return LOADED_SUCCESSFULLY;
	}
	catch (const std::exception&)
	{
		return FAILED_TO_LOAD;
	}
}

void loadingScreen() {
	using namespace variables;
	using namespace std::chrono_literals;

	std::future<FileLoadStatus> f = std::async(std::launch::async, loadHostelDB);
	
	int textGenDelay = int(targetFPS / 2);
	int textGenCounter = 0;

	std::string randomLoadingText = getRandomString(true);

	while (f.wait_for(1us) != std::future_status::ready && !WindowShouldClose())
	{
		// --------- Logic -----------------

		if (textGenCounter > textGenDelay) {
			randomLoadingText = getRandomString(true);
			textGenCounter = 0;
		}
		else {
			textGenCounter++;
		}

		// --------- Drawing GUI -----------
		BeginDrawing();
		ClearBackground(H_DARK_GREY);
		drawCustomText(randomLoadingText.c_str(), Vector2{ 400, 600 }, labels, 1, H_WHITE);
		animateBugCatGIF(Vector2{ 0, 400 });
		EndDrawing();
	}

	f.wait();
	FileLoadStatus fileStatus = f.get();

	switch (fileStatus)
	{
	case variables::DOES_NOT_EXIST:

		BeginDrawing();
		ClearBackground(H_DARK_GREY);
		drawCustomText("Hostel File Does Not Exist :(", Vector2{10, 10}, labels, 1, H_WHITE);
		EndDrawing();
		std::this_thread::sleep_for(std::chrono::seconds(2));

		currentLayer = CREATE_NEW_HOSTEL_SCREEN;

		currentLayer = FATAL_ERROR_SCREEN;
		break;
	case variables::LOADED_SUCCESSFULLY:
		break;
	case variables::FAILED_TO_LOAD:
		break;
	default:
		currentLayer = FATAL_ERROR_SCREEN;
		break;
	}
}