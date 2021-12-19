#include "EditorScene.hpp"

void Scenes::EditorScene::Start() {
    std::cout << "On Editor Scene" << std::endl;
}

void Scenes::EditorScene::Update() {
    glClearColor(RGBANORM(167.0f, 250.0f, 214.0f, 255.0f));
}

void Scenes::EditorScene::GuiUpdate() {
    ImGui::Begin("Performance");
    ImGui::Text("FPS: %.1f", (0.001f / ((float)Time::deltaTime() / 1000.0f)));

    ImGui::End();
}
