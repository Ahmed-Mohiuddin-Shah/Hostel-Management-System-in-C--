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

class GUIToggleButton {
private:
    Rectangle bounds;
    std::string value1;
    std::string value2;
    std::string label;
    bool state;

public:
    GUIToggleButton() {

    }

    GUIToggleButton(float x, float y, std::string option1, std::string option2, std::string label) : state(false) {
        value1 = option1;
        value2 = option2;
        this->label = label;
        this->bounds = Rectangle{ x, y, ((value1.length() > value2.length() ? value1.length() : value2.length()) + label.length()) * variables::widthPerCharacterForLabels , variables::labelsTextHeight };
    }

    void update() {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(GetMousePosition(), bounds)) {
            state = !state;
        }
    }

    void draw() const {
        DrawRectangleRounded(bounds, 0.5, 10, state ? variables::H_BLUE : variables::H_DARK_BLUE);
        DrawRectangleRoundedLines(bounds, 0.5, 10, 5, state ? variables::H_DARK_BLUE : variables::H_BLUE);
        drawCustomText(TextFormat("%s%s", label.c_str(), state ? value1.c_str() : value2.c_str()), Vector2{bounds.x + 0.5f, bounds.y  + 0.5f}, variables::labels, 1, variables::H_WHITE);
    }

    void updatePositionX(int xPos) {
        bounds.x = xPos;
    }

    std::string getValue() const {
        return state ? value1.c_str() : value2.c_str();
    }

    bool getState() {
        return state;
    }

    void setState(bool state) {
        this->state = state;
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
    bool showCursor;
    float cursorTimer;
    const float cursorBlinkSpeed = 0.5;

public:
    TextInputBox(float x, float y, const char* boxLabel, bool numberField, int bufferSize)
        : bounds({ x, y, variables::widthPerCharacterForLabels * (bufferSize + 4 + TextLength(boxLabel)), variables::labelsTextHeight }), labelBounds({ x, y, variables::widthPerCharacterForLabels * (TextLength(boxLabel) + 1), variables::labelsTextHeight }), label(boxLabel), isSelected(false), isNumericField(numberField) {
        // Initialize text buffer
        this->bufferSize = bufferSize + 1;
        text = new char[bufferSize + 1];
        text[0] = '\0';
        showCursor = false;
        cursorTimer = 0.0f;
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
    
        if (isSelected && showCursor) {
            DrawLine(bounds.x + labelBounds.width + 15 + (TextLength(text) * variables::widthPerCharacterForLabels), bounds.y + bounds.height / 2 - 10,
                bounds.x + labelBounds.width + 15 + (TextLength(text) * variables::widthPerCharacterForLabels), bounds.y + bounds.height / 2 + 10, variables::H_WHITE);
        }

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

        if (isSelected) {
            cursorTimer += GetFrameTime();
            if (cursorTimer >= cursorBlinkSpeed) {
                showCursor = !showCursor;
                cursorTimer = 0.0f;  // Reset the timer
            }
        }
        else {
            showCursor = false;  // Reset cursor visibility when not selected
            cursorTimer = 0.0f;
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
    GUIToggleButton modeToggleButton;
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
        buttons.push_back(GUISideBarButton{ sideBarBounds.x + buttonOffset, 120, variables::ADD_STUDENT_SCREEN, "Add/Delete Student", false });
        buttons.push_back(GUISideBarButton{ sideBarBounds.x + buttonOffset, 160, variables::PROMOTE_STUDENTS_SCREEN, "Promote Students", false });
        buttons.push_back(GUISideBarButton{ sideBarBounds.x + buttonOffset, 210, variables::ROOM_DETAILS_SCREEN, "Room Deets", false });
        buttons.push_back(GUISideBarButton{ sideBarBounds.x + buttonOffset, 250, variables::ADD_ROOM_SCREEN, "Add/Delete Room", false });
        buttons.push_back(GUISideBarButton{ sideBarBounds.x + buttonOffset, 300, variables::STAFF_DETAILS_SCREEN, "Staff Deets", false });
        buttons.push_back(GUISideBarButton{ sideBarBounds.x + buttonOffset, 340, variables::ADD_STAFF_SCREEN, "Add Staff", false });
        buttons.push_back(GUISideBarButton{ sideBarBounds.x + buttonOffset, 380, variables::REMOVE_STAFF_SCREEN, "Remove Staff", false });
        buttons.push_back(GUISideBarButton{ sideBarBounds.x + buttonOffset, 430, variables::GET_SPECIFIC_INVOICE_SCREEN, "All Invoices", false });
        buttons.push_back(GUISideBarButton{ sideBarBounds.x + buttonOffset, 470, variables::GENERATE_INVOICES_SCREEN, "Generate Invoice", false });
        // buttons.push_back(GUISideBarButton{ sideBarBounds.x + buttonOffset, 550, variables::DISPLAY_INVOICES_SCREEN, "Display Invoices", false });
        buttons.push_back(GUISideBarButton{ sideBarBounds.x + buttonOffset, 510, variables::MARK_INVOICE_PAID_SCREEN, "Mark Invoice Paid", false });
        buttons.push_back(GUISideBarButton{ sideBarBounds.x + buttonOffset + 250, 670, variables::EXIT_SCREEN, "Exit", true });

        modeToggleButton = GUIToggleButton(sideBarBounds.x + buttonOffset, 560, "Serious", "Fun", " Mode: ");

        infoBoxes.push_back(Rectangle{ sideBarBounds.x + rectOffset + 60, 10, width - rectOffset - 145, 45 });
        infoBoxes.push_back(Rectangle{ sideBarBounds.x + rectOffset, 70, width - rectOffset - 10, 125 });
        infoBoxes.push_back(Rectangle{ sideBarBounds.x + rectOffset, 200, width - rectOffset - 10, 85 });
        infoBoxes.push_back(Rectangle{ sideBarBounds.x + rectOffset, 290, width - rectOffset - 10, 125 });
        infoBoxes.push_back(Rectangle{ sideBarBounds.x + rectOffset, 420, width - rectOffset - 10, 125 });

        textOffset = width - 20;

        textPositions.push_back({ Vector2{ sideBarBounds.x + textOffset, 80} , "Students"});
        textPositions.push_back({ Vector2{ sideBarBounds.x + textOffset, 210 }, "Rooms"});
        textPositions.push_back({ Vector2{ sideBarBounds.x + textOffset, 300 }, "Staff"});
        textPositions.push_back({ Vector2{ sideBarBounds.x + textOffset, 430 }, "Invoices"});
    }

    void checkToChangeLayer() {
        for (auto& button : buttons) {
            if (button.isClicked()) {
                variables::currentLayer = button.getScreenLayer();
            }
        }
        modeToggleButton.setState(hostelInstance.getMode());
        modeToggleButton.update();
        hostelInstance.setMode(modeToggleButton.getState());
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

        modeToggleButton.updatePositionX(sideBarBounds.x + buttonOffset);

    }

    void draw() {
        DrawRectangleRounded(sideBarBounds, 0.1, 10, variables::H_BLUE);
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

        modeToggleButton.draw();


        // if Serious mode is off
        if (!hostelInstance.getMode()) {
            animateBugCatGIF(Vector2{ sideBarBounds.x + 10, variables::burgerMenuBugCatPosition.y });
        }
        
    }
};


class GUIScrollView {
private:
    Vector2 bounds;
    std::string data;
    int scrollPosition;
    int height;

public:
    GUIScrollView(float x, float y, const std::string& formattedString)
        : bounds{ x, y }, data(formattedString), scrollPosition(0) {
        height = (countNewLineCharacters(formattedString) - 3) / 2 * variables::labelsTextHeight;
    }

    void update() {
        // Adjust scroll position based on mouse wheel movement
        scrollPosition -= GetMouseWheelMove() * 20;

        // Ensure scroll position is within valid range
        scrollPosition = (scrollPosition < 0) ? 0 : scrollPosition;

        if (scrollPosition > height) {
            scrollPosition = height;
        }
    }

    void draw() const {

        drawCustomText(data.c_str(), Vector2{ bounds.x, bounds.y - scrollPosition }, variables::labels, 1, variables::H_WHITE);
    }

    void setText(std::string formattedString) {
        data = formattedString;
        height = (countNewLineCharacters(formattedString) - 3) / 2 * variables::labelsTextHeight;
        scrollPosition = 0;
    }
};

class Popup {
protected:
    Rectangle bounds;
    Vector2 position;
    std::string message;
    int messageLength = 300;
    float slideSpeed;
    float originalDisplayTime;
    float displayTime;
    bool isVisible;

public:
    void showMessage(const std::string& message) {
        this->message = message;

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

    virtual void draw() const = 0;
};

class ErrorPopup : public Popup{
private:

public:
    ErrorPopup(float slideSpeed, float displayTime) {
        this->slideSpeed = slideSpeed; 
        this->originalDisplayTime = displayTime;
        this->displayTime = displayTime;
        this->isVisible = false;
        this->bounds = { variables::screenWidth, 15, 320, 60 };
        this->position = { variables::screenWidth, 20 };
    }
  
    void draw() const {
        if (isVisible) {
            
            DrawRectangleRounded(bounds, 0.5, 5, RED);
            DrawTexture(hostelInstance.getMode() ? variables::errorTexture : variables::errorCatTexture, bounds.x, bounds.y, WHITE);
            DrawRectangleRoundedLines(bounds, 0.5, 10, 8, MAROON);
            drawCustomText(TextFormat("     %s", message.c_str()), Vector2{position.x + 10, position.y + 10}, variables::labels, 1, variables::H_WHITE);
        }
    }
};

class SuccessPopup :public Popup {
private:

public:
    SuccessPopup(float slideSpeed, float displayTime) {
        this->slideSpeed = slideSpeed;
        this->originalDisplayTime = displayTime;
        this->displayTime = displayTime;
        this->isVisible = false;
        this->bounds = { variables::screenWidth, 15, 320, 60 };
        this->position = { variables::screenWidth, 20 };
    }

    void draw() const {
        if (isVisible) {

            DrawRectangleRounded(bounds, 0.5, 5, GREEN);
            DrawTexture(hostelInstance.getMode() ? variables::successTexture : variables::successCatTexture, bounds.x, bounds.y, WHITE);
            DrawRectangleRoundedLines(bounds, 0.5, 10, 8, DARKGREEN);
            drawCustomText(TextFormat("     %s", message.c_str()), Vector2{ position.x + 10, position.y + 10 }, variables::labels, 1, variables::H_WHITE);
        }
    }

    bool isFinished() {
        return isVisible;
    }
};