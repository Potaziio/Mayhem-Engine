#include "MouseListener.hpp"

void Mayhem::Input::MouseListener::MouseCursorCallback(GLFWwindow* window, double xpos, double ypos) {
    Mayhem::Input::MouseListener::lastMousePos = Math::Vector2f(mousePos.x, mousePos.y);
    Mayhem::Input::MouseListener::mousePos = Math::Vector2f((float)xpos, (float)ypos);
}

void Mayhem::Input::MouseListener::MouseScrollCallback(GLFWwindow* window, double xOffset, double yOffset) {
    MouseListener::mouseScroll = (float)yOffset;
}

void Mayhem::Input::MouseListener::MouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
    if (action == GLFW_PRESS) {
        if (button < MOUSEBUTTONS) {
            MouseListener::mouseHold[button] = true;
            MouseListener::mouseDown[button] = true;
        }
    }
    else if (action == GLFW_RELEASE) {
        MouseListener::mouseHold[button] = false;
        MouseListener::mouseUp[button] = true;
        MouseListener::isDragging = false;
    }
}

void Mayhem::Input::MouseListener::endMouseFrame() {
    MouseListener::lastMousePos = Math::Vector2f(MouseListener::mousePos.x, MouseListener::mousePos.y);
    MouseListener::mouseScroll = 0.0f;
    MouseListener::isDragging = MouseListener::mouseHold[0];
    
    for (int i = 0; i < MOUSEBUTTONS; ++i) {
        MouseListener::mouseDown[i] = false;
        MouseListener::mouseUp[i] = false;
    }
}


Mayhem::Math::Vector2f Mayhem::Input::MouseListener::GetMousePos() {
    return MouseListener::mousePos; 
}

Mayhem::Math::Vector2f Mayhem::Input::MouseListener::GetLastMousePos() {
    return MouseListener::lastMousePos; 
}

Mayhem::Math::Vector2f Mayhem::Input::MouseListener::GetDeltaMousePos() {
    return MouseListener::mousePos - MouseListener::lastMousePos;
}

float Mayhem::Input::MouseListener::GetMouseScroll() {
    return MouseListener::mouseScroll;
}

bool Mayhem::Input::MouseListener::isMouseDragging() {
    return MouseListener::isDragging;
}

bool Mayhem::Input::MouseListener::GetMouseButton(int button) {
    if (button < MOUSEBUTTONS) { return mouseHold[button]; }
    return false;
} 

bool Mayhem::Input::MouseListener::GetMouseButtonDown(int button) {
    if (button < MOUSEBUTTONS) { return mouseDown[button]; }
    return false;
}

bool Mayhem::Input::MouseListener::GetMouseButtonUp(int button) {
    if (button < MOUSEBUTTONS) { return mouseUp[button]; }
    return false;
}

// Static variables

bool Mayhem::Input::MouseListener::mouseHold[MOUSEBUTTONS];
bool Mayhem::Input::MouseListener::mouseDown[MOUSEBUTTONS];
bool Mayhem::Input::MouseListener::mouseUp[MOUSEBUTTONS];
bool Mayhem::Input::MouseListener::isDragging;
float Mayhem::Input::MouseListener::mouseScroll;

Mayhem::Math::Vector2f Mayhem::Input::MouseListener::mousePos;
Mayhem::Math::Vector2f Mayhem::Input::MouseListener::lastMousePos;

