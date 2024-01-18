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
public:
    GUISideBarButton(float x, float y, variables::LAYERS screenLayer, const char* buttonText) {
        this->bounds = Rectangle{ x, y, TextLength(buttonText) * variables::widthPerCharacterForsideBarButtonText , variables::sideBarButtonTextHeight };
        this->layerIdentifier = screenLayer;
        this->text = buttonText;
    }

    bool isMouseOver() {
        return CheckCollisionPointRec(GetMousePosition(), bounds);
    }

    void draw() {
        DrawRectangleRounded(bounds, 0.5, 10, isMouseOver() ? variables::H_BLUE : variables::H_DARK_BLUE);
        DrawRectangleRoundedLines(bounds, 0.5, 10, 5, isMouseOver() ? variables::H_DARK_BLUE : variables::H_BLUE);
        drawCustomText(text, Vector2{ bounds.x + TextLength(text) / 2, bounds.y + 2.0f }, variables::sideBarButtonText, 1, variables::H_WHITE);
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
    char text[64];
    bool isSelected;

public:
    TextInputBox(float x, float y, const char* boxLabel)
        : bounds({ x, y, variables::widthPerCharacterForLabels * (63 + TextLength(boxLabel)), variables::labelsTextHeight }), labelBounds({ x, y, variables::widthPerCharacterForLabels * (TextLength(boxLabel) + 1), variables::labelsTextHeight }), label(boxLabel), isSelected(false) {
        // Initialize text buffer
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
                if ((key >= 32) && (key <= 125) && (strlen(text) < sizeof(text) - 1)) {
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

    Rectangle getBounds() {
        return bounds;
    }
};

class GUISidebar {
private:
    Rectangle sideBarBounds;
    float closedPositionX;
    std::vector<GUISideBarButton> buttons;
    const int buttonOffset = 65;

public:
    GUISidebar(float width) {
        closedPositionX = -width - width/10;
        sideBarBounds = Rectangle{ closedPositionX, 0, width, variables::screenHeight };
        buttons.push_back(GUISideBarButton{ sideBarBounds.x + buttonOffset + 120, 20, variables::HOSTEL_DETAILS_SCREEN, "Hostel Deets" });
        buttons.push_back(GUISideBarButton{ sideBarBounds.x + buttonOffset + 60, 20, variables::HOME_SCREEN, "Home" });
        buttons.push_back(GUISideBarButton{ sideBarBounds.x + buttonOffset, 100, variables::FATAL_ERROR_SCREEN, "Student Deets" });
        buttons.push_back(GUISideBarButton{ sideBarBounds.x + buttonOffset, 100, variables::FATAL_ERROR_SCREEN, "Student Deets" });
        buttons.push_back(GUISideBarButton{ sideBarBounds.x + buttonOffset, 140, variables::FATAL_ERROR_SCREEN, "Add Student" });
        buttons.push_back(GUISideBarButton{ sideBarBounds.x + buttonOffset, 180, variables::FATAL_ERROR_SCREEN, "Promote Students" });
        buttons.push_back(GUISideBarButton{ sideBarBounds.x + buttonOffset, 220, variables::FATAL_ERROR_SCREEN, "Remove Student" });
        buttons.push_back(GUISideBarButton{ sideBarBounds.x + buttonOffset, 260, variables::FATAL_ERROR_SCREEN, "Room Deets" });
        buttons.push_back(GUISideBarButton{ sideBarBounds.x + buttonOffset, 300, variables::FATAL_ERROR_SCREEN, "Add Room" });
        buttons.push_back(GUISideBarButton{ sideBarBounds.x + buttonOffset, 340, variables::FATAL_ERROR_SCREEN, "Staff Deets" });
        buttons.push_back(GUISideBarButton{ sideBarBounds.x + buttonOffset, 380, variables::FATAL_ERROR_SCREEN, "Add Staff" });
        buttons.push_back(GUISideBarButton{ sideBarBounds.x + buttonOffset, 420, variables::FATAL_ERROR_SCREEN, "Delete Staff" });
        buttons.push_back(GUISideBarButton{ sideBarBounds.x + buttonOffset, 460, variables::FATAL_ERROR_SCREEN, "Generate Invoice" });
        buttons.push_back(GUISideBarButton{ sideBarBounds.x + buttonOffset, 500, variables::FATAL_ERROR_SCREEN, "Display Invoices" });
        buttons.push_back(GUISideBarButton{ sideBarBounds.x + buttonOffset, 540, variables::FATAL_ERROR_SCREEN, "Get Invoice"});
    }

    void checkToChangeLayer() {
        for (auto& button : buttons) {
            if (button.isClicked()) {
                variables::currentLayer = button.getScreenLayer();
            }
        }
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

        for (auto& button : buttons) {
            if (button.getScreenLayer() == variables::HOSTEL_DETAILS_SCREEN) {
                button.setPosition(sideBarBounds.x + buttonOffset + 120);
                continue;
            }
            if (button.getScreenLayer() == variables::HOME_SCREEN) {
                button.setPosition(sideBarBounds.x + buttonOffset + 60);
                continue;
            }
            button.setPosition(sideBarBounds.x + buttonOffset);
        }

    }

    void draw() {
        DrawRectangleRounded(sideBarBounds, 0.2, 10, variables::H_BLUE);
        DrawRectangle(sideBarBounds.x, sideBarBounds.y, (sideBarBounds.width / 2), sideBarBounds.height, variables::H_BLUE);


        // drawButtons
        for (auto& button : buttons) {
            button.draw();
        }


        animateBugCatGIF(Vector2{ sideBarBounds.x + 10, variables::burgerMenuBugCatPosition.y });
    }
};