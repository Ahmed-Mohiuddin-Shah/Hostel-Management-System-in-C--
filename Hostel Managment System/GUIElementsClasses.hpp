#pragma once

class GUIButton {
private:
    Rectangle bounds;
    const char* text;
public:
    GUIButton(float x, float y, float width, float height, const char* buttonText) {
        this->bounds = Rectangle{ x, y, width, height };
        this->text = buttonText;
    }

    bool isMouseOver() {
        return CheckCollisionPointRec(GetMousePosition(), bounds);
    }

    void draw() {
        DrawRectangleRec(bounds, isMouseOver() ? variables::H_DARK_BLUE : variables::H_BLUE);
        drawCustomText(text, Vector2{ bounds.x + 0.5f, bounds.y + 0.5f }, variables::labels, 1, variables::H_WHITE);
    }

    bool isClicked() {
        return isMouseOver() && IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
    }
};