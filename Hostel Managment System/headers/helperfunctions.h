#pragma once

// ----------- Initializing Functions ---------------------
void initializeVariables() {

    using namespace variables;

    // ------------- Fonts Initialization -----------------
    customFont = LoadFontEx(customFontPath, maxFontSize, 0, 250);

    // ------------- GIF Animation Initialization ---------
    bugCatGIFImage = LoadImageAnim(bugCatGIFPath, &animFrames);
    bugCatTexture = LoadTextureFromImage(bugCatGIFImage);
}

// ----------- Custom Text Drawing Function ---------------
void drawCustomText(const char* text, Vector2 position, float fontSize, float spacing, Color colorTint) {
    DrawTextEx(variables::customFont, text, position, fontSize, spacing, colorTint);
}

// ----------- GIF Drawing --------------------------------
void animateGIF(Vector2 position) {
    using namespace variables;
    frameCounter++;
    if (frameCounter >= frameDelay)
    {
        currentAnimFrame++;
        if (currentAnimFrame >= animFrames) currentAnimFrame = 0;
        nextFrameDataOffset = bugCatGIFImage.width * bugCatGIFImage.height * 4 * currentAnimFrame;
        UpdateTexture(bugCatTexture, ((unsigned char*)bugCatGIFImage.data) + nextFrameDataOffset);
        frameCounter = 0;
    }
    DrawTexture(bugCatTexture, position.x, position.y, H_WHITE);
}

void unloadResources() {
    using namespace variables;
    UnloadTexture(bugCatTexture);
    UnloadImage(bugCatGIFImage);
}