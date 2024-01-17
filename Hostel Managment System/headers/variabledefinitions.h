#pragma once

namespace variables {

	// ------------- Misc ----------------------------


	// ------------- Color Palette -------------------
	Color H_DARK_GREY = { 68, 72, 68, 255 };
	Color H_BLUE = { 91, 129, 232, 255 };
	Color H_DARK_BLUE = { 73, 103, 197, 255 };
	Color H_WHITE = WHITE;

	// ------------- Fonts ---------------------------
	Font customFont;
	const char* customFontPath = "resources/ComicCode.otf";

	// ------------- Font Sizing ---------------------
	float maxFontSize = 200;
	float headings = 150;
	float labels = 50;

	// ------------- Screen Size ---------------------
	const int screenWidth = 1280;
	const int screenHeight = 720;

	// ------------- GIF Animation -------------------
	const char* bugCatGIFPath = "resources/bugcatgif.gif";
	int animFrames = 0;
	Image bugCatGIFImage;
	Texture2D bugCatTexture;
	unsigned int nextFrameDataOffset = 0;
	int currentAnimFrame = 0;
	int frameDelay = 3;
	int frameCounter = 0;

	// -------------- Screen Layers ------------------
	enum LAYERS
	{
		LOADING_SCREEN
	};

	LAYERS currentLayer = LOADING_SCREEN;

	// -------------- 
}