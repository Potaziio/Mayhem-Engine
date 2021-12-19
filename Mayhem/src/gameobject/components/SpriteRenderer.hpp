#ifndef SPRITERENDERER_H
#define SPRITERENDERER_H

#include "Component.hpp"
#include "../../util/Shader.hpp"
#include "../GameObject.hpp"

#include "../../math/vector/Vector4f.hpp"

namespace Mayhem {
    namespace ECS {
        namespace Components {
            class SpriteRenderer : public Component {
                private:
                    unsigned int VAO, VBO, EBO;
                    unsigned int* indices;
                    float* vertices;

                    bool wasInitialized = false;

                    bool isRect = false;
                    bool isTriangle = false;
                public:
                    GameObject* gameObject;
                    std::string GetComponentType() override {return "Sprite Renderer";}

                    Utils::Shader* shader;

                    Math::Vector4f color;
                    
                    ~SpriteRenderer();
                    SpriteRenderer(Utils::Shader* shader, Math::Vector4f color);
                    void genRectVertices();
                    void genRectIndices();
                    void CreateRect();
                    void CreateTriangle() {}

                    void DrawRect();
                    void DrawTriangle() {}
            };
        }
    }
}


#endif /* ifndef SPRITERENDERER_H */
