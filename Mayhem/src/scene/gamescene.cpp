#include "GameScene.hpp"

// TODO: Implement 2D rotation (Look into quaternions and euler angles)

// TODO: Logging class

// TODO: AssetPool, Constructor takes in a name and a shader, (Map that has the shader name as key and the shader as val)
// When given a shader name, if it already exists it will check the key to see and the shader path to see if its the same
// If it is the same it will skip, if its a different one it will skip and warn the user

// TODO: Read from map csv file and create a map out of it using instanced rendering

Shader* shader = new Shader("../Mayhem/assets/shaders/defaultmesh.glsl");

GameObject* Player = new GameObject("Player", Transform(Vector3f(0.0f, 0.0f, 0.0f), Vector3f(0.5f, 0.5f, 0.0f), Vector3f(1.0f, 1.0f, 1.0f)));

float playerSpeed = 700.0f;

ImVec4 win_color = ImVec4(167.0f / 255.0f, 0.0f, 214.0f / 255.0f , 255.0f / 255.0f);

Vector4f colorTest = Vector4f(RGBANORM(255.0f, 255.0f, 0.0f, 20.0f));

void Scenes::GameScene::Start() {
    std::cout << "On Runtime Scene" << std::endl;
    shader->compile();
    this->OrthoCamera = new ECS::OrthographicCamera(Vector3f(0.0f, 0.0f, 0.0f), -(float)Window::getWidth() * 0.5f, 
            (float)Window::getWidth() * 0.5f, -(float)Window::getHeight() * 0.5f, (float)Window::getHeight() * 0.5f, 0.0f, 100.0f );
    
    Player->AddComponent(SpriteRenderer(shader, Vector4f(RGBANORM(255.0f, 255.0f, 0.0f, 255.0f)), Draw::Sprite2D::Rect()));

    this->addGameObjectToScene(Player);
    this->addGameObjectToScene(OrthoCamera);
}

void Scenes::GameScene::Update() {
    glClearColor(win_color.x, win_color.y, win_color.z, win_color.w);
    
    Vector3f movement = Vector3f(Input::KeyboardListener::GetAxisRaw("Horizontal"), Input::KeyboardListener::GetAxisRaw("Vertical"), 0.0f);
    movement.Normalize();

    Player->transform->position += (movement * playerSpeed) * Time::deltaTime();
}

void Scenes::GameScene::GuiUpdate() {
    ImGui::Begin("Window");
    ImGui::Text("FPS: %.1f", (0.001f / ((float)Time::deltaTime() / 1000.0f)));
    ImGui::ColorEdit4("Window Color", (float*)&win_color);
    ImGui::End();
    
    ImGui::Begin("Camera Settings");
    ImGui::DragFloat3("Position", (float*)&this->OrthoCamera->transform->position);
    ImGui::End();
    
    ImGui::Begin("Player Settings");
    ImGui::ColorEdit4("Color", (float*)&Player->GetComponent<SpriteRenderer>()->color);
    ImGui::DragFloat3("Position", (float*)&Player->transform->position);
    ImGui::DragFloat3("Scale", (float*)&Player->transform->scale, 0.0f, 500.0f);
    ImGui::DragFloat3("Rotation", (float*)&Player->transform->rotation, 0.0f, 360.0f);
    ImGui::SliderFloat("Speed: ", &playerSpeed, 0.0f, 1000.0f);
    
    ImGui::End();
}
