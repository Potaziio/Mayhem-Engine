#ifndef WINDOW_H
#define WINDOW_H

#include <iostream>
#include <memory>

#include "../../../include/vendor/glew-2.2.0/include/GL/glew.h"
#include "../../../include/vendor/glfw-3.3.5/include/GLFW/glfw3.h"

#include "../../../include/vendor/imgui-docking/imgui.h"
#include "../../../include/vendor/imgui-docking/imgui_impl_opengl3.h"
#include "../../../include/vendor/imgui-docking/imgui_impl_glfw.h"

#include "../input/KeyboardListener.hpp"
#include "../input/MouseListener.hpp"

#include "../util/Time.hpp"

#include "../camera/Camera.hpp"

#include "../scene/Scene.hpp"
#include "../scene/GameScene.hpp"
#include "../scene/EditorScene.hpp"

class Window;
#include "../imguilayer/ImGuiLayer.hpp"

namespace Mayhem {
    class Window {
        private:
            static GLFWwindow* window;
            static int width;
            static int height;
            static const char* name;

            static Mayhem::Scenes::Scene* currentScene;
        public:
            static GLFWwindow* getWindow() {return window;}
            static int getWidth() {return width;}
            static int getHeight() {return height;}
            static const char* getName() {return name;}

            static Mayhem::Scenes::Scene* getCurrentScene() {return currentScene;} 

            static void changeScene(enum Scenes::Scene::SCENETYPE);

            Window(const char* name, int width, int height);

            static void WindowFramebufferSizeCallback(GLFWwindow* window, int width, int height);
            void update();
            void freeMemory();
    };
}

#endif /* ifndef WINDOW_H */
