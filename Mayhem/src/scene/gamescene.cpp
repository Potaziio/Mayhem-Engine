#include "GameScene.hpp"

Shader* shader = new Shader("../Mayhem/assets/shaders/defaultmesh.glsl");

GameObject* player = new GameObject("Player");

void Scenes::GameScene::Start() {
    std::cout << "On Runtime Scene" << std::endl;

    shader->compile();
    this->OrthoCamera = new OrthographicCamera(Vector3f(0.0f, 0.0f, 0.0f), -960, 960.0f, -540, 540.0f, 0.0f, 100.0f);

    player->AddComponent(SpriteRenderer(shader, Vector4f(RGBANORM(255.0f, 255.0f, 0.0f, 255.0f))));

    this->addGameObjectToScene(OrthoCamera);
    this->addGameObjectToScene(player);
}

void Scenes::GameScene::Update() {
    glClearColor(RGBANORM(167.0f, 0.0f, 214.0f, 255.0f));
}

void Scenes::GameScene::GuiUpdate() {
}
