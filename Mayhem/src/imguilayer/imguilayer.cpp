#include "ImGuiLayer.hpp"

void Mayhem::Utils::UI::ImGuiLayer::init() {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGuiIO& io = ImGui::GetIO(); (void)io;

    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(Window::getWindow(), true);
    ImGui_ImplOpenGL3_Init("#version 130");
}


void Mayhem::Utils::UI::ImGuiLayer::setupDockspace() {
	ImGuiWindowFlags windowFlags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;

    ImGui::SetNextWindowPos(ImVec2(0.0f, 0.0f), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(Window::getWidth(), Window::getHeight()));

    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);

    windowFlags |= ImGuiWindowFlags_NoTitleBar | 
    ImGuiWindowFlags_NoCollapse |
    ImGuiWindowFlags_NoResize | 
    ImGuiWindowFlags_NoMove | 
    ImGuiWindowFlags_NoBringToFrontOnFocus |
    ImGuiWindowFlags_NoNavFocus;

    bool show = true;

    ImGui::Begin("Dockspace", &show, windowFlags);
    ImGui::PopStyleVar(2);

    ImGuiIO& io = ImGui::GetIO();

    // Dockspace
    if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable) {
    	ImGuiID dockspace = ImGui::GetID("Dockspace");
    	ImGui::DockSpace(dockspace, ImVec2(0.0f, 0.0f));
    }


}


void Mayhem::Utils::UI::ImGuiLayer::update() {
	ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
	setupDockspace();
	Window::getCurrentScene()->GuiUpdate();
	ImGui::End();
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}