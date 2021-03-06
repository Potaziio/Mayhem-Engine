#include "Scene.hpp"

void Mayhem::Scenes::Scene::freeSceneMemory() {
    for (auto& go : gameObjects) {
        printf("deleting: '%s' memory.\n", go.second->getName().c_str());
        for(auto& co : go.second->GetComponents()) {
            delete co.second;
        }
        delete go.second;
    }
}

void Mayhem::Scenes::Scene::removeGameObject(ECS::GameObject* go) {
    if (gameObjects.find(go->getID().id()) != gameObjects.end()) { return; }
    gameObjects.erase(go->getID().id());
}

void Mayhem::Scenes::Scene::addGameObjectToScene(ECS::GameObject* go) {
    if (gameObjects.find(go->getID().id()) != gameObjects.end()) { return; } 
    gameObjects[go->getID().id()] = go;
}

Mayhem::ECS::GameObject* Mayhem::Scenes::Scene::GetGameObject(std::string name) {
    bool found = true;
    
    for (auto& go : gameObjects) {
        if (go.second->getName() == name) {
            found = true;
            return go.second;
        } 
    }
    
    if (!found) {
        std::cout << "ERROR::NO::GAMEOBJECT::FOUND" << std::endl;
        return nullptr;
    }
    
    return nullptr;
}

void Mayhem::Scenes::Scene::onSceneStart() {
    
}

void Mayhem::Scenes::Scene::onRuntimeUpdate() {
    // Update view and projection matrices for ortho cameara
    if (this->sceneCamera == ORTHOGRAPHIC)
        OrthoCamera->update(); 
    else 
        PerspectiveCamera->update();
    
    for (auto& go : gameObjects) {
        if (go.second->HasComponent<ECS::Components::SpriteRenderer>()) {
            ECS::Components::SpriteRenderer* spriterenderer = go.second->GetComponent<ECS::Components::SpriteRenderer>();
            
            spriterenderer->shader->use();

            if (this->sceneCamera == ORTHOGRAPHIC) {
                spriterenderer->shader->sendMat4("view", OrthoCamera->GetViewMatrix());
                spriterenderer->shader->sendMat4("projection", OrthoCamera->GetProjectionMatrix());
            } else {
                spriterenderer->shader->sendMat4("view", PerspectiveCamera->GetViewMatrix());
                spriterenderer->shader->sendMat4("projection", PerspectiveCamera->GetProjectionMatrix());
            }

            spriterenderer->render();
            spriterenderer->shader->detach();
        }
    }
}

std::unordered_map<std::string, Mayhem::ECS::GameObject*> Mayhem::Scenes::Scene::GetGameObjects() {
    return this->gameObjects;
}
