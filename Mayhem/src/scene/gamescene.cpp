#include "GameScene.hpp"

// TODO: Logging class

// TODO: AssetPool, Constructor takes in a name and a shader, (Map that has the shader name as key and the shader as val)
// When given a shader name, if it already exists it will check the key to see and the shader path to see if its the same
// If it is the same it will skip, if its a different one it will skip and warn the user

// TODO: Read from map csv file and create a map out of it using instanced rendering  

// TODO: Add way to add all components of gameobject in GameObject constructor 

Shader* shader = new Shader("../Mayhem/assets/shaders/defaultmesh.glsl");

GameObject* Player = new GameObject("Player", Transform(Vector3f(0.0f, 0.0f, 0.0f), Vector3f(30.0f, 30.0f)));

float playerSpeed = 570.0f;

void Scenes::GameScene::Start() {
    std::cout << "On Runtime Scene" << std::endl;
    shader->compile();
    this->OrthoCamera = new OrthographicCamera(Vector3f(0.0f, 0.0f, 0.0f), -960, 960.0f, 540, -540.0f, 0.0f, 100.0f);

    Player->AddComponent(SpriteRenderer(shader, Vector4f(RGBANORM(255.0f, 255.0f, 255.0f, 255.0f))));

    this->addGameObjectToScene(Player);
    this->addGameObjectToScene(OrthoCamera);
}

void Scenes::GameScene::Update() {
    glClearColor(RGBANORM(167.0f, 0.0f, 214.0f, 255.0f));

    Vector3f movement = Vector3f(Input::KeyboardListener::GetAxisRaw("Horizontal"), Input::KeyboardListener::GetAxisRaw("Vertical"), 0.0f);
    movement.Normalize();

    Player->transform->position += (movement * playerSpeed) * Time::deltaTime();
}

void Scenes::GameScene::GuiUpdate() {
    ImGui::Begin("Performance");
    ImGui::Text("FPS: %.1f", (0.001f / ((float)Time::deltaTime() / 1000.0f)));

    ImGui::End();

    ImGui::Begin("Player Settings");

    ImGui::SliderFloat("Speed: ", &playerSpeed, 0.0f, 1000.0f);

    ImGui::End();
}
