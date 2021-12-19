#ifndef MOUSELISTENER_H
#define MOUSELISTENER_H value

#include "../../../include/vendor/glfw-3.3.5/include/GLFW/glfw3.h"
#include "../math/vector/Vector2f.hpp"

#define MOUSEBUTTONS 4

namespace Mayhem {
    namespace Input {
        class MouseListener {
            private:
                static bool mouseHold[MOUSEBUTTONS];
                static bool mouseDown[MOUSEBUTTONS];
                static bool mouseUp[MOUSEBUTTONS];
                static bool isDragging;
                static float mouseScroll;

                static Math::Vector2f mousePos;
                static Math::Vector2f lastMousePos;
            public:
                static void MouseCursorCallback(GLFWwindow* window, double xpos, double ypos);
                static void MouseScrollCallback(GLFWwindow* window, double xOffset, double yOffset);
                static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
                static void endMouseFrame(); 

                static float GetMouseScroll();
                static Math::Vector2f GetLastMousePos();
                static Math::Vector2f GetMousePos();
                static Math::Vector2f GetDeltaMousePos();

                static bool isMouseDragging();
                static bool GetMouseButtonDown(int button);
                static bool GetMouseButtonUp(int button);
                static bool GetMouseButton(int button); 
        };
    }
}


#endif /* ifndef MOUSELISTENER_H */
