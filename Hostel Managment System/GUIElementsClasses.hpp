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

    bool isClicked() {
        return isMouseOver() && IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
    }

    Rectangle getBounds() {
        return bounds;
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
    TextInputBox(float x, float y,  const char* boxLabel)
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

public:
    GUISidebar(float width) {
        closedPositionX = -width - width/10;
        sideBarBounds = Rectangle{ closedPositionX, 0, width, variables::screenHeight };
    }

    void shouldShow(bool show) {
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

    }

    void draw() {
        DrawRectangleRounded(sideBarBounds, 0.2, 10, variables::H_BLUE);
        DrawRectangle(sideBarBounds.x, sideBarBounds.y, (sideBarBounds.width / 2), sideBarBounds.height, variables::H_BLUE);
        animateBugCatGIF(Vector2{ sideBarBounds.x + 10, variables::burgerMenuBugCatPosition.y });
    }
};