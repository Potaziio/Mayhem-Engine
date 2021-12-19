#include "EditorScene.hpp"

Shader* shader = new Shader("../Mayhem/assets/shaders/defaultmesh.glsl");

GameObject* player = new GameObject("Player");

void Scenes::EditorScene::Start() {
    shader->compile();
    this->OrthoCamera = new OrthographicCamera(Vector3f(0.0f, 0.0f, 0.0f), 0.0f, 1600.0f, 1000.0f, 0.0f, 0.0f, 100.0f);

    player->AddComponent(SpriteRenderer(shader, Vector4f(RGBANORM(255.0f, 0.0f, 0.0f, 255.0f))));


    this->addGameObjectToScene(player);
    this->addGameObjectToScene(OrthoCamera);

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
