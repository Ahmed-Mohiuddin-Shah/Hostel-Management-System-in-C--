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
    Image fatalErrorImage = LoadImage("resources/fatalErrorCat.png");
    fatalErrorTexture = LoadTextureFromImage(fatalErrorImage);
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
    // save hostel info
    return false;
}