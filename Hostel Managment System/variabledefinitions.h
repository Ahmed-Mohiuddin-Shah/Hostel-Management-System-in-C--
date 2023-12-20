#pragma once

namespace variables {

	// ------------- Misc ----------------------------
	const int targetFPS = 60;
	bool shouldExit = false;

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
	float widthPerCharacterForHeadings = 66;
	float labels = 25;
	float labelsTextHeight = 30;
	float widthPerCharacterForLabels = 12;
	float sideBarButtonText = 18;
	float sideBarButtonTextHeight = 25;
	float widthPerCharacterForsideBarButtonText = 10;

	// ------------- Screen Size ---------------------
	const int screenWidth = 1280;
	const int screenHeight = 720;

	// ------------- BugCat GIF Animation ------------
	const char* bugCatGIFPath = "resources/bugcatgif.gif";
	int animBugCatFrames = 0;
	Image bugCatGIFImage;
	Texture2D bugCatTexture;
	unsigned int nextBugCatFrameDataOffset = 0;
	int currentBugCatAnimFrame = 0;
	int frameBugCatDelay = 3;
	int frameBugCatCounter = 0;
	Vector2 burgerMenuBugCatPosition = { 0, 550 };

	// ------------- Fatal Error Texture -------------
	Texture2D fatalErrorTexture;
	Texture2D fatalErrorCatTexture;
	// ------------- Success Texture -----------------
	Texture2D successTexture;
	Texture2D successCatTexture;
	// ------------- Error Texture -------------------
	Texture2D errorTexture;
	Texture2D errorCatTexture;

	// -------------- Screen Layers ------------------
	enum LAYERS
	{
		LOADING_SCREEN,
		FATAL_ERROR_SCREEN,
		CREATE_NEW_HOSTEL_SCREEN,
		HOSTEL_DETAILS_SCREEN,
		HOME_SCREEN,
		STUDENT_DETAILS_SCREEN,
		ROOM_DETAILS_SCREEN,
		STAFF_DETAILS_SCREEN,
		DISPLAY_INVOICES_SCREEN,
		ADD_STUDENT_SCREEN,
		PROMOTE_STUDENTS_SCREEN,
		ADD_ROOM_SCREEN,
		ADD_STAFF_SCREEN,
		REMOVE_STAFF_SCREEN,
		GENERATE_INVOICES_SCREEN,
		GET_SPECIFIC_INVOICE_SCREEN,
		MARK_INVOICE_PAID_SCREEN,
		EXIT_SCREEN
	};

	LAYERS currentLayer = LOADING_SCREEN;
	LAYERS previousLayer = LOADING_SCREEN;

	// -------------- File Loading -------------------
	enum FileLoadStatus {
		DOES_NOT_EXIST,
		LOADED_SUCCESSFULLY,
		FILE_EMPTY,
		FAILED_TO_LOAD
	};

	std::string fileContent = "";
	JSON hostelJSON;

	// --------------- Overlay -----------------------
	bool globalBurgerButtonToggleState = false;
	bool globalShouldShowSuccessPopup = false;
	bool globalShouldShowRoomNotAvailableErrorPopup = false;
	std::string successPopupMessage = "Ye!";
	std::string fatalErrorMessage = "Not Implemented Yet!";
}