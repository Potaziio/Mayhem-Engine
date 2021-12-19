#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "Scene.hpp"

#include <iostream>

#include "../util/MayhemUtil.hpp"
#include "../util/Time.hpp"

#include "../../../include/vendor/glew-2.2.0/include/GL/glew.h"
#define GLFW_INCLUDE_NONE
#include "../../../include/vendor/glfw-3.3.5/include/GLFW/glfw3.h"

#include "../input/KeyboardListener.hpp"
#include "../input/MouseListener.hpp"
#include "../util/MayhemUtil.hpp"
#include "../gameobject/GameObject.hpp"

#include "../../../include/vendor/imgui/imgui.h"
#include "../../../include/vendor/imgui/imgui_impl_opengl3.h"
#include "../../../include/vendor/imgui/imgui_impl_glfw.h"

// Forward referece
class GameScene;
#include "../window/Window.hpp"

using namespace Mayhem;
using namespace Mayhem::Utils;
using namespace Mayhem::ECS;

namespace Mayhem {
    namespace Scenes {
        class GameScene : public Scene {
            public:
                GameScene() {}
                void Start() override;
                void Update() override;
                void GuiUpdate() override;
        };
    }
}

#endif /* ifndef  GAMESCENE_H */
