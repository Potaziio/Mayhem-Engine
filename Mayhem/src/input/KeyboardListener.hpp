#ifndef KEYBOARDLISTENER_H
#define KEYBOARDLISTENER_H

#include <iostream>

#define GLFW_INCLUDE_NONE
#include "../../../include/vendor/glfw-3.3.5/include/GLFW/glfw3.h"

#define KEYBOARDKEYS 350

namespace Mayhem {
    namespace Input {
        class KeyboardListener {
            private:
                static bool keyHold[KEYBOARDKEYS];
                static bool keyDown[KEYBOARDKEYS];
                static bool keyUp[KEYBOARDKEYS];
            public:
                static bool GetKeyDown(int key);
                static bool GetKeyUp(int key);
                static bool GetKey(int key);

                static float GetAxisRaw(std::string axis);

                static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
                static void endKeyFrame();
        };
    }
}

#endif /* ifndef KEYBOARDLISTENER_H */
