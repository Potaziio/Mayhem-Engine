#include "ImGuiLayer.hpp"

void Mayhem::Utils::UI::ImGuiLayer::init() {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGuiIO& io = ImGui::GetIO(); (void)io;

    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(Window::getWindow(), true);
    ImGui_ImplOpenGL3_Init("#version 130");
}

void Mayhem::Utils::UI::ImGuiLayer::update() {
	ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

	Window::getCurrentScene()->GuiUpdate();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
