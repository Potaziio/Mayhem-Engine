#ifndef SPRITERENDERER_H
#define SPRITERENDERER_H

#include "Component.hpp"
#include "../../util/Shader.hpp"
#include "../GameObject.hpp"

#include "../../sprite/Sprite.hpp"

#include "../../math/vector/Vector4f.hpp"

namespace Mayhem {
    namespace ECS {
        namespace Components {
            class SpriteRenderer : public Component {
                private:
                    Draw::Sprite2D::BaseSprite* sprite;
                public:
                    GameObject* gameObject;
                    std::string GetComponentType() override {return "Sprite Renderer";}
                    void OnImGui() override;

                    enum SPRITESTATE {
                        CLEAN,
                        DIRTY
                    };

                    SPRITESTATE spriteState = CLEAN;

                    Utils::Shader* shader;

                    Math::Vector4f color;

                    void UpdateSpriteAttributes();

                    template <typename T>
                        SpriteRenderer(Utils::Shader* shader, Math::Vector4f color, T sprite): shader(shader), color(color), sprite(new T(sprite)) {
                            this->sprite->color = color * 10;
                            this->sprite->init();
                        }

                    void render();
            };
        }
    }
}


#endif /* ifndef SPRITERENDERER_H */
