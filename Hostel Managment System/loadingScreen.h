#pragma once

variables::FileLoadStatus loadHostelDB() {
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

	while (f.wait_for(1us) != std::future_status::ready && !WindowShouldClose())   // increment loopCounter after evaluating condition
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
		drawCustomText(randomLoadingText.c_str(), Vector2{ 10, 10 }, labels, 1, H_WHITE);
		EndDrawing();
	}

	f.wait();
	FileLoadStatus fileStatus = f.get();

	switch (fileStatus)
	{
	case variables::DOES_NOT_EXIST:
		currentLayer = FATAL_ERROR;
		break;
	case variables::LOADED_SUCCESSFULLY:
		break;
	case variables::FAILED_TO_LOAD:
		break;
	default:
		currentLayer = FATAL_ERROR;
		break;
	}
}