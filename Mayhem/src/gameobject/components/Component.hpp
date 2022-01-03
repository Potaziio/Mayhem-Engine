#ifndef COMPONENT_H
#define COMPONENT_H

#include <iostream>

#include "../../../../include/vendor/imgui-docking/imgui.h"
#include "../../../../include/vendor/imgui-docking/imgui_impl_opengl3.h"
#include "../../../../include/vendor/imgui-docking/imgui_impl_glfw.h"

namespace Mayhem {
    namespace ECS {
        namespace Components {
            class Component {
                public:
                    virtual std::string GetComponentType() {}
                    virtual void OnImGui() {}
                    virtual ~Component() {}
            };
        }
    }
}

#endif /* ifndef COMPONENT_H */
