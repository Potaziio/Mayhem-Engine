#ifndef IMGUILAYER_H 
#define IMGUILAYER_H

#include "../../../include/vendor/glew-2.2.0/include/GL/glew.h"
#define GLFW_INCLUDE_NONE
#include "../../../include/vendor/glfw-3.3.5/include/GLFW/glfw3.h"

#include "../../../include/vendor/imgui-docking/imgui.h"
#include "../../../include/vendor/imgui-docking/imgui_impl_opengl3.h"
#include "../../../include/vendor/imgui-docking/imgui_impl_glfw.h"

#include "../window/Window.hpp"

namespace Mayhem {
	namespace Utils {
		namespace UI {
			class ImGuiLayer {
				public:
					static void init();
					static void update();
					static void setupDockspace();
			};
		}
	}
}


#endif 