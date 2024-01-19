#pragma once

class GUIButton {
private:
    Rectangle bounds;
    const char* text;
public:
    GUIButton(float x, float y, const char* buttonText) {
        this->bounds = Rectangle{ x, y, TextLength(buttonText) * variables::widthPerCharacterForLabels , variables::labelsTextHeight};
        this->text = buttonText;
    }

    bool isMouseOver() {
        return CheckCollisionPointRec(GetMousePosition(), bounds);
    }

    void draw() {
        DrawRectangleRounded(bounds, 0.5, 10, isMouseOver() ? variables::H_BLUE : variables::H_DARK_BLUE);
        DrawRectangleRoundedLines(bounds, 0.5, 10, 5, isMouseOver() ? variables::H_DARK_BLUE : variables::H_BLUE);
        drawCustomText(text, Vector2{ bounds.x + TextLength(text) / 2, bounds.y + 2.0f}, variables::labels, 1, variables::H_WHITE);
    }

    void setPosition(int xPosition) {
        bounds.x = xPosition;
    }

    bool isClicked() {
        return isMouseOver() && IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
    }

    Rectangle getBounds() {
        return bounds;
    }
};

class GUISideBarButton {
private:
    Rectangle bounds;
    variables::LAYERS layerIdentifier;
    const char* text;
    bool isExitButton;
public:
    GUISideBarButton(float x, float y, variables::LAYERS screenLayer, const char* buttonText, bool isExitButton) {
        this->bounds = Rectangle{ x, y, TextLength(buttonText) * variables::widthPerCharacterForsideBarButtonText , variables::sideBarButtonTextHeight };
        this->layerIdentifier = screenLayer;
        this->text = buttonText;
        this->isExitButton = isExitButton;
    }

    bool isMouseOver() {
        return CheckCollisionPointRec(GetMousePosition(), bounds);
    }

    void draw() {
        if (!isExitButton) {
            DrawRectangleRounded(bounds, 0.5, 10, isMouseOver() ? variables::H_BLUE : variables::H_DARK_BLUE);
            DrawRectangleRoundedLines(bounds, 0.5, 10, 5, isMouseOver() ? variables::H_DARK_BLUE : variables::H_BLUE);
            drawCustomText(text, Vector2{ bounds.x + TextLength(text) / 2, bounds.y + 2.0f }, variables::sideBarButtonText, 1, variables::H_WHITE);
        }
        else {
            DrawRectangleRounded(bounds, 0.7, 10, isMouseOver() ? MAROON : RED);
            DrawRectangleRoundedLines(bounds, 0.7, 10, 5, isMouseOver() ? RED : MAROON);
            drawCustomText(text, Vector2{ bounds.x + TextLength(text) / 2, bounds.y + 2.0f }, variables::sideBarButtonText, 1, variables::H_WHITE);
        }
    }

    void setPosition(int xPosition) {
        bounds.x = xPosition;
    }

    bool isClicked() {
        return isMouseOver() && IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
    }

    Rectangle getBounds() {
        return bounds;
    }

    variables::LAYERS getScreenLayer() {
        return layerIdentifier;
    }
};

class GUIBurgerButton {
private:
    Rectangle bounds;
    Texture2D unToggledImageTexture;
    Texture2D toggledImageTexture;
    bool isToggled;

    bool isMouseOver() {
        return CheckCollisionPointRec(GetMousePosition(), bounds);
    }

    bool isClicked() {
        return isMouseOver() && IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
    }

public:
    GUIBurgerButton(float x, float y) {
        Image imageToggled = LoadImage("resources/toggledBurgerButton.png");
        Image imageUnToggled = LoadImage("resources/unToggledBurgerButton.png");
        this->unToggledImageTexture = LoadTextureFromImage(imageUnToggled);
        this->toggledImageTexture = LoadTextureFromImage(imageToggled);
        this->bounds = Rectangle{ x, y, float(unToggledImageTexture.width), float (unToggledImageTexture.height)};
        this->isToggled = false;
        UnloadImage(imageToggled);
        UnloadImage(imageUnToggled);
    }

    ~GUIBurgerButton()
    {
        UnloadTexture(unToggledImageTexture);
        UnloadTexture(toggledImageTexture);
    }

    void draw() {
        DrawRectangleRec(bounds, isMouseOver() ? variables::H_DARK_BLUE : variables::H_BLUE);

        if (isToggled) {
            DrawTexture(toggledImageTexture, bounds.x, bounds.y, variables::H_WHITE);
        }
        else {
            DrawTexture(unToggledImageTexture, bounds.x, bounds.y, variables::H_WHITE);
        }

        if (isClicked()) {
            isToggled = !isToggled;
            variables::globalBurgerButtonToggleState = isToggled;
        }
    }

    bool isButtonToggled() {
        return isToggled;
    }

    void setButtonToggled(bool toggleState) {
        isToggled = toggleState;
    }
};

class TextInputBox {
private:
    Rectangle bounds;
    Rectangle labelBounds;
    const char* label;
    int bufferSize;
    char *text;
    bool isSelected;
    bool isNumericField;

public:
    TextInputBox(float x, float y, const char* boxLabel, bool numberField, int bufferSize)
        : bounds({ x, y, variables::widthPerCharacterForLabels * (bufferSize + 2 + TextLength(boxLabel)), variables::labelsTextHeight }), labelBounds({ x, y, variables::widthPerCharacterForLabels * (TextLength(boxLabel) + 1), variables::labelsTextHeight }), label(boxLabel), isSelected(false), isNumericField(numberField) {
        // Initialize text buffer
        this->bufferSize = bufferSize + 1;
        text = new char[bufferSize + 1];
        text[0] = '\0';
    }


    bool isActive() {
        return this->isSelected;
    }

    void deSelect() {
        this->isSelected = false;
    }

    void draw() const {

        DrawRectangleRounded(bounds, 0.5, 10, variables::H_DARK_GREY);
        DrawRectangleRounded(labelBounds, 0.5, 10, isSelected ? variables::H_BLUE : variables::H_DARK_BLUE);

        DrawRectangleRoundedLines(bounds, 0.5, 10, 5, isSelected ? variables::H_DARK_BLUE : variables::H_BLUE);
        DrawRectangleRoundedLines(labelBounds, 0.5, 10, 5, isSelected ? variables::H_DARK_BLUE : variables::H_BLUE);

        drawCustomText(TextFormat("%s  %s", label, text), Vector2{ bounds.x + 10, bounds.y + bounds.height / 2 - 10 }, variables::labels, 1, variables::H_WHITE);
    }

    void update() {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(GetMousePosition(), bounds)) {
            isSelected = !isSelected;
        }

        if (isSelected) {
            int key = GetCharPressed();

            while (key > 0) {
                if (isNumericField && (key >= '0' && key <= '9') && (strlen(text) < bufferSize - 1)) {
                    // Only accept numeric characters when isNumeric is true
                    int len = strlen(text);
                    text[len] = static_cast<char>(key);
                    text[len + 1] = '\0';
                }
                else if (!isNumericField && (key >= 32) && (key <= 125) && (strlen(text) < bufferSize - 1)) {
                    // Accept alphanumeric characters when isNumeric is false
                    int len = strlen(text);
                    text[len] = static_cast<char>(key);
                    text[len + 1] = '\0';
                }

                key = GetCharPressed();
            }

            if (IsKeyPressed(KEY_BACKSPACE) && (strlen(text) > 0)) {
                text[strlen(text) - 1] = '\0';
            }
        }
    }

    std::string getInputText() {
        return std::string(text);
    }

    Rectangle getBounds() {
        return bounds;
    }
};

struct SideBarInfoText {
    Vector2 position;
    const char* text;
};

class GUISidebar {
private:
    Rectangle sideBarBounds;
    Rectangle outsideBounds;
    float closedPositionX;
    std::vector<GUISideBarButton> buttons;
    std::vector<Rectangle> infoBoxes;
    std::vector<SideBarInfoText> textPositions;
    const int buttonOffset = 65;
    const int rectOffset = 55;
    int textOffset;

public:
    GUISidebar(float width) {
        closedPositionX = -width + width/10;
        sideBarBounds = Rectangle{ closedPositionX, 0, width, variables::screenHeight };
        outsideBounds = Rectangle{ width - width/10, 0, variables::screenWidth - width + width/2, variables::screenHeight };

        buttons.push_back(GUISideBarButton{ sideBarBounds.x + buttonOffset + 120, 20, variables::HOSTEL_DETAILS_SCREEN, "Hostel Deets", false });
        buttons.push_back(GUISideBarButton{ sideBarBounds.x + buttonOffset + 60, 20, variables::HOME_SCREEN, "Home", false });
        buttons.push_back(GUISideBarButton{ sideBarBounds.x + buttonOffset, 80, variables::STUDENT_DETAILS_SCREEN, "Student Deets", false });
        buttons.push_back(GUISideBarButton{ sideBarBounds.x + buttonOffset, 120, variables::ADD_STUDENT_SCREEN, "Add Student", false });
        buttons.push_back(GUISideBarButton{ sideBarBounds.x + buttonOffset, 160, variables::FATAL_ERROR_SCREEN, "Promote Students", false });
        buttons.push_back(GUISideBarButton{ sideBarBounds.x + buttonOffset, 200, variables::FATAL_ERROR_SCREEN, "Remove Student", false });
        buttons.push_back(GUISideBarButton{ sideBarBounds.x + buttonOffset, 250, variables::ROOM_DETAILS_SCREEN, "Room Deets", false });
        buttons.push_back(GUISideBarButton{ sideBarBounds.x + buttonOffset, 290, variables::ADD_ROOM_SCREEN, "Add Room", false });
        buttons.push_back(GUISideBarButton{ sideBarBounds.x + buttonOffset, 340, variables::STAFF_DETAILS_SCREEN, "Staff Deets", false });
        buttons.push_back(GUISideBarButton{ sideBarBounds.x + buttonOffset, 380, variables::ADD_STAFF_SCREEN, "Add Staff", false });
        buttons.push_back(GUISideBarButton{ sideBarBounds.x + buttonOffset, 420, variables::FATAL_ERROR_SCREEN, "Delete Staff", false });
        buttons.push_back(GUISideBarButton{ sideBarBounds.x + buttonOffset, 470, variables::FATAL_ERROR_SCREEN, "Generate Invoice", false });
        buttons.push_back(GUISideBarButton{ sideBarBounds.x + buttonOffset, 510, variables::DISPLAY_INVOICES_SCREEN, "Display Invoices", false });
        buttons.push_back(GUISideBarButton{ sideBarBounds.x + buttonOffset, 550, variables::FATAL_ERROR_SCREEN, "Get Invoice", false });
        buttons.push_back(GUISideBarButton{ sideBarBounds.x + buttonOffset + 250, 670, variables::EXIT_SCREEN, "Exit", true });

        infoBoxes.push_back(Rectangle{ sideBarBounds.x + rectOffset + 60, 10, width - rectOffset - 145, 45 });
        infoBoxes.push_back(Rectangle{ sideBarBounds.x + rectOffset, 70, width - rectOffset - 10, 165 });
        infoBoxes.push_back(Rectangle{ sideBarBounds.x + rectOffset, 240, width - rectOffset - 10, 85 });
        infoBoxes.push_back(Rectangle{ sideBarBounds.x + rectOffset, 330, width - rectOffset - 10, 125 });
        infoBoxes.push_back(Rectangle{ sideBarBounds.x + rectOffset, 460, width - rectOffset - 10, 125 });

        textOffset = width - 20;

        textPositions.push_back({ Vector2{ sideBarBounds.x + textOffset, 80} , "Students"});
        textPositions.push_back({ Vector2{ sideBarBounds.x + textOffset, 250 }, "Rooms"});
        textPositions.push_back({ Vector2{ sideBarBounds.x + textOffset, 340 }, "Staff"});
        textPositions.push_back({ Vector2{ sideBarBounds.x + textOffset, 470 }, "Invocie"});
    }

    void checkToChangeLayer() {
        for (auto& button : buttons) {
            if (button.isClicked()) {
                variables::currentLayer = button.getScreenLayer();
            }
        }
    }

    bool isMouseClickedOutsideOfSideBar() {
        return CheckCollisionPointRec(GetMousePosition(), outsideBounds) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
    }

    void shouldShowUpdate(bool show) {
        float targetX = show ? 0.0f : closedPositionX;

        if (abs(sideBarBounds.x - targetX) == sideBarBounds.width / 10) {
            return;
        }

        if (sideBarBounds.x > targetX) {
            sideBarBounds.x -= sideBarBounds.width / 10;
        }
        else {
            sideBarBounds.x += sideBarBounds.width / 10;
        }

        for (auto& infoBox : infoBoxes) {
            if (infoBox.y == 10) {
                infoBox.x = sideBarBounds.x + rectOffset + 60;
                continue;
            }
            infoBox.x = sideBarBounds.x + rectOffset;
        }

        for (auto& textPosition : textPositions) {
            textPosition.position.x = sideBarBounds.x + textOffset;
        }

        for (auto& button : buttons) {
            if (button.getScreenLayer() == variables::HOSTEL_DETAILS_SCREEN) {
                button.setPosition(sideBarBounds.x + buttonOffset + 120);
                continue;
            }
            if (button.getScreenLayer() == variables::HOME_SCREEN) {
                button.setPosition(sideBarBounds.x + buttonOffset + 60);
                continue;
            }
            if (button.getScreenLayer() == variables::EXIT_SCREEN) {
                button.setPosition(sideBarBounds.x + buttonOffset + 270);
                continue;
            }
            button.setPosition(sideBarBounds.x + buttonOffset);
        }

    }

    void draw() {
        DrawRectangleRounded(sideBarBounds, 0.2, 10, variables::H_BLUE);
        DrawRectangle(sideBarBounds.x, sideBarBounds.y, (sideBarBounds.width / 2), sideBarBounds.height, variables::H_BLUE);

        // draw info boxes
        for (auto& infoBox : infoBoxes) {
            if (infoBox.y == 10) {
                DrawRectangleRounded(infoBox, 0.4, 10, variables::H_DARK_GREY);
                continue;
            }
            DrawRectangleRounded(infoBox, 0.2, 10, variables::H_DARK_GREY);
        }

        for (auto& textPosition : textPositions) {
            DrawTextPro(variables::customFont, textPosition.text, textPosition.position, Vector2{0, 0}, 90.0, variables::labels, 1, variables::H_WHITE);
        }

        // drawButtons
        for (auto& button : buttons) {
            button.draw();
        }


        animateBugCatGIF(Vector2{ sideBarBounds.x + 10, variables::burgerMenuBugCatPosition.y });
    }
};

class ErrorPopup {
private:
    Rectangle bounds;
    Vector2 position;
    Texture2D errorTexture;
    std::string message;
    int messageLength = 300;
    float slideSpeed;
    float originalDisplayTime;
    float displayTime;
    bool isVisible;

public:
    ErrorPopup(float slideSpeed, float displayTime) : slideSpeed(slideSpeed), originalDisplayTime(displayTime), displayTime(displayTime), isVisible(false) {
        bounds = { variables::screenWidth, 15, 320, 60 };
        position = { variables::screenWidth, 20 };
        Image errorCat = LoadImage("resources/errorCat.png");
        errorTexture = LoadTextureFromImage(errorCat);
        UnloadImage(errorCat);
    }

    ~ErrorPopup()
    {
        UnloadTexture(errorTexture);
    }

    void showMessage(const std::string& errorMessage) {
        message = errorMessage;

        std::string delimiter = "\n";
        std::string token1 = message.substr(0, message.find(delimiter));
        std::string token2 = message.substr(message.find(delimiter) + 1, message.length());

        messageLength = ((token1.length() > token2.length() ? token1.length() : token2.length()) + 5) * variables::widthPerCharacterForLabels;
        bounds.width = messageLength + 100 ;
        isVisible = true;
    }

    void update() {
        if (isVisible) {
            // Slide in
            if (bounds.x > variables::screenWidth - messageLength) {
                position.x -= slideSpeed * GetFrameTime();
                bounds.x -= slideSpeed * GetFrameTime();
            }


            // Check if time to display has elapsed
            displayTime -= GetFrameTime();
            if (displayTime <= 0) {
                isVisible = false;
                displayTime = originalDisplayTime;
            }
        }
        else {
            position = { variables::screenWidth, 10 };
            bounds.x = variables::screenWidth;
        }
    }
  
    void draw() const {
        if (isVisible) {
            
            DrawRectangleRounded(bounds, 0.5, 5, RED);
            DrawTexture(errorTexture, bounds.x, bounds.y, WHITE);
            DrawRectangleRoundedLines(bounds, 0.5, 10, 8, MAROON);
            drawCustomText(TextFormat("     %s", message.c_str()), Vector2{position.x + 10, position.y + 10}, variables::labels, 1, variables::H_WHITE);
        }
    }
};

class SuccessPopup {
private:
    Rectangle bounds;
    Vector2 position;
    Texture2D successTexture;
    std::string message;
    int messageLength = 300;
    float slideSpeed;
    float originalDisplayTime;
    float displayTime;
    bool isVisible;

public:
    SuccessPopup(float slideSpeed, float displayTime) : slideSpeed(slideSpeed), originalDisplayTime(displayTime), displayTime(displayTime), isVisible(false) {
        bounds = { variables::screenWidth, 15, 320, 60 };
        position = { variables::screenWidth, 20 };
        Image successCat = LoadImage("resources/successCat.png");
        successTexture = LoadTextureFromImage(successCat);
        UnloadImage(successCat);
    }

    ~SuccessPopup()
    {
        UnloadTexture(successTexture);
    }

    void showMessage(const std::string& successMessage) {
        message = successMessage;

        std::string delimiter = "\n";
        std::string token1 = message.substr(0, message.find(delimiter));
        std::string token2 = message.substr(message.find(delimiter) + 1, message.length());

        messageLength = ((token1.length() > token2.length() ? token1.length() : token2.length()) + 5) * variables::widthPerCharacterForLabels;
        bounds.width = messageLength + 100;
        isVisible = true;
    }

    void update() {
        if (isVisible) {
            // Slide in
            if (bounds.x > variables::screenWidth - messageLength) {
                position.x -= slideSpeed * GetFrameTime();
                bounds.x -= slideSpeed * GetFrameTime();
            }


            // Check if time to display has elapsed
            displayTime -= GetFrameTime();
            if (displayTime <= 0) {
                isVisible = false;
                displayTime = originalDisplayTime;
            }
        }
        else {
            position = { variables::screenWidth, 10 };
            bounds.x = variables::screenWidth;
        }
    }

    void draw() const {
        if (isVisible) {

            DrawRectangleRounded(bounds, 0.5, 5, GREEN);
            DrawTexture(successTexture, bounds.x, bounds.y, WHITE);
            DrawRectangleRoundedLines(bounds, 0.5, 10, 8, DARKGREEN);
            drawCustomText(TextFormat("     %s", message.c_str()), Vector2{ position.x + 10, position.y + 10 }, variables::labels, 1, variables::H_WHITE);
        }
    }

    bool isFinished() {
        return isVisible;
    }
};