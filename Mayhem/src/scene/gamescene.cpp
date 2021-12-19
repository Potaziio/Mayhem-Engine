#include "GameScene.hpp"

void Scenes::GameScene::Start() {
    std::cout << "On Runtime Scene" << std::endl;
}

void Scenes::GameScene::Update() {
    glClearColor(RGBANORM(167.0f, 0.0f, 214.0f, 255.0f));

    if (Input::KeyboardListener::GetKeyDown(GLFW_KEY_LEFT)) {
        Window::changeScene(this->EDITORSCENE);        
    }
}

void Scenes::GameScene::GuiUpdate() {
}
