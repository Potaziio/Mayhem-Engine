#ifndef SCENE_H
#define SCENE_H

#include <iostream>
#include <unordered_map>
#include <vector>
#include "../camera/Camera.hpp"
#include "../gameobject/GameObject.hpp"
#include "../gameobject/components/Transform.hpp"
#include "../gameobject/components/SpriteRenderer.hpp"

namespace Mayhem {
    namespace Scenes {
        class Scene {
            std::unordered_map<std::string, ECS::GameObject*> gameObjects; 
            public:
            Scene() {}
            virtual void Update() {}
            virtual void Start() {}
            virtual void GuiUpdate() {}

            ECS::OrthographicCamera* OrthoCamera;
            ECS::PerspectiveCamera* PerspectiveCamera;

            void freeSceneMemory();

            void addGameObjectToScene(ECS::GameObject* go);
            void removeGameObject(ECS::GameObject* go);
            ECS::GameObject* GetGameObject(std::string name);

            void onSceneStart();
            void onEditorUpdate();
            void onRuntimeUpdate();

            enum SCENECAMERA {
                PERSPECTIVE,
                ORTHOGRAPHIC,
            };

            enum SCENETYPE {
                RUNTIMESCENE,
            };

            SCENETYPE sceneType;
            SCENECAMERA sceneCamera = PERSPECTIVE;

            std::unordered_map<std::string, ECS::GameObject*> GetGameObjects();
        };
    }
}



#endif /* ifndef SCENE_H */
