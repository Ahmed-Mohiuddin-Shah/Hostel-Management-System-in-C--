#pragma once

// ----------- Initializing Functions ---------------------
void initializeVariables() {

    using namespace variables;

    // ------------- Fonts Initialization -----------------
    customFont = LoadFontEx(customFontPath, maxFontSize, 0, 250);

    // ------------- GIF Animation Initialization ---------
    bugCatGIFImage = LoadImageAnim(bugCatGIFPath, &animBugCatFrames);
    bugCatTexture = LoadTextureFromImage(bugCatGIFImage);

    // ------------- Fatal Error Texture Load -------------
    Image fatalErrorImage = LoadImage("resources/fatalError.png");
    fatalErrorTexture = LoadTextureFromImage(fatalErrorImage);
    fatalErrorImage = LoadImage("resources/fatalErrorCat.png");
    fatalErrorCatTexture = LoadTextureFromImage(fatalErrorImage);
    UnloadImage(fatalErrorImage);

    // ------------- Success Texture Load -----------------
    Image successImage = LoadImage("resources/success.png");
    successTexture = LoadTextureFromImage(successImage);
    successImage = LoadImage("resources/successCat.png");
    successCatTexture = LoadTextureFromImage(successImage);
    UnloadImage(successImage);

    // ------------- Error texture Load -------------------
    Image errorImage = LoadImage("resources/error.png");
    errorTexture = LoadTextureFromImage(errorImage);
    errorImage = LoadImage("resources/errorCat.png");
    errorCatTexture = LoadTextureFromImage(errorImage);
    UnloadImage(errorImage);

}

// ----------- Custom Text Drawing Function ---------------
void drawCustomText(const char* text, Vector2 position, float fontSize, float spacing, Color colorTint) {
    DrawTextEx(variables::customFont, text, position, fontSize, spacing, colorTint);
}

void drawCustomBodyText(const char* text, Vector2 position, float fontSize, float spacing, Color colorTint) {
    DrawTextEx(variables::customFont, text, Vector2 {position.x + 90, position.y}, fontSize, spacing, colorTint);
}

// ----------- GIF Drawing --------------------------------
void animateBugCatGIF(Vector2 position) {
    using namespace variables;
    frameBugCatCounter++;
    if (frameBugCatCounter >= frameBugCatDelay)
    {
        currentBugCatAnimFrame++;
        if (currentBugCatAnimFrame >= animBugCatFrames) currentBugCatAnimFrame = 0;
        nextBugCatFrameDataOffset = bugCatGIFImage.width * bugCatGIFImage.height * 4 * currentBugCatAnimFrame;
        UpdateTexture(bugCatTexture, ((unsigned char*)bugCatGIFImage.data) + nextBugCatFrameDataOffset);
        frameBugCatCounter = 0;
    }
    DrawTexture(bugCatTexture, position.x, position.y, H_WHITE);
}

bool layerChangedHandler() {
    if (variables::previousLayer != variables::currentLayer) {
        variables::previousLayer = variables::currentLayer;
        variables::globalBurgerButtonToggleState = false;
        return true;
    }
    return false;
}

bool writeHostelInfoToFile() {
    std::this_thread::sleep_for(std::chrono::seconds(3));

    try
    {
        std::string hostelInfoStringDump = hostelInstance.toJson().dump(4);
        FileReader::writeToFile(ProjectInfo::fileName, hostelInfoStringDump);
        return true;
    }
    catch (const std::exception e)
    {
        variables::fatalErrorMessage = e.what() + std::string("\nFailed To Save Hostel Info!\nTry To Exit Again!");
        return false;
    }

}

int countNewLineCharacters(std::string s) {
    int count = 0;

    for (int i = 0; i < s.size(); i++)
        if (s[i] == '\n') count++;

    return count;
}