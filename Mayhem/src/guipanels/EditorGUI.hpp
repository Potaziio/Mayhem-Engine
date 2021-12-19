#ifndef EDITORGUI
#define EDITORGUI


#include "../math/MathUtils.hpp"
#include "../math/vector/Vector2f.hpp"
#include "../util/MayhemUtil.hpp"
#include "../util/Time.hpp"
#include "../gameobject/GameObject.hpp"

#include "../gameobject/components/SpriteRenderer.hpp"

#include "../scene/Scene.hpp"

#include "../window/Window.hpp"

#include "../../../include/vendor/imgui/imgui.h"
#include "../../../include/vendor/imgui/imgui_impl_opengl3.h"
#include "../../../include/vendor/imgui/imgui_impl_glfw.h"
#include "../../../include/vendor/imgui/imstb_textedit.h"
#include "../../../include/vendor/imgui/imstb_rectpack.h"

namespace Mayhem {
    namespace Utils {
        namespace GUI {
            class EditorGUI {
                public:
                    static void onEditorGuiUpdate();
            };
        }
    }
}


#endif /* ifndefu EDITORGUI */
