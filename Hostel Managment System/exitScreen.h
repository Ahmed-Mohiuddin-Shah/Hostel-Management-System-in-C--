#pragma once

void exitScreen() {
	using namespace variables;
	using namespace std::chrono_literals;

	std::future<bool> f = std::async(std::launch::async, writeHostelInfoToFile);

	int textGenDelay = int(targetFPS / 2);
	int textGenCounter = 0;

	std::string randomLoadingText = getRandomString(false);
	
	while (f.wait_for(1us) != std::future_status::ready)
	{
		// --------- Logic -----------------

		if (textGenCounter > textGenDelay) {
			randomLoadingText = getRandomString(false);
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
	bool fileWriteStatus = f.get();

	if (!fileWriteStatus) {
		currentLayer = FATAL_ERROR_SCREEN;
		return;
	}
	shouldExit = true;
}