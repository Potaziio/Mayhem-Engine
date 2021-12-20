#include "KeyboardListener.hpp"

void Mayhem::Input::KeyboardListener::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS) {
        keyHold[key] = true;
        keyDown[key] = true;
    } else if (action == GLFW_RELEASE) {
        keyHold[key] = false;
        keyUp[key] = true;
    }
}

void Mayhem::Input::KeyboardListener::endKeyFrame() {
    for (int i = 0; i < KEYBOARDKEYS; ++i) {
        keyDown[i] = false;
        keyUp[i] = false;
    }    
}

float Mayhem::Input::KeyboardListener::GetAxisRaw(std::string axis) {
    if (axis == "Horizontal") {
        if (GetKey(GLFW_KEY_D)) {
            return 1.0f;
        } else if (GetKey(GLFW_KEY_A)) {
            return -1.0f;
        }
    }

    if (axis == "Vertical") {
        if (GetKey(GLFW_KEY_W)) {
            return 1.0f;
        } else if (GetKey(GLFW_KEY_S)) {
            return -1.0f;
        }
    }

    return 0.0f;
}

bool Mayhem::Input::KeyboardListener::GetKeyDown(int key) {
    return keyDown[key];
} 


bool Mayhem::Input::KeyboardListener::GetKeyUp(int key) {
    return keyUp[key];
}  

bool Mayhem::Input::KeyboardListener::GetKey(int key) {
    return keyHold[key]; 
}  

bool Mayhem::Input::KeyboardListener::keyHold[KEYBOARDKEYS];
bool Mayhem::Input::KeyboardListener::keyDown[KEYBOARDKEYS];
bool Mayhem::Input::KeyboardListener::keyUp[KEYBOARDKEYS]; 
