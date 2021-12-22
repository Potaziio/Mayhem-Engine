#include "SpriteRenderer.hpp"
#include "Component.hpp"

void Mayhem::ECS::Components::SpriteRenderer::render() {
    if (this->color != this->sprite->color) {
        spriteState = DIRTY;
    }

    if (spriteState != CLEAN) {
        UpdateSpriteAttributes();
        spriteState = CLEAN;
    }

    shader->sendMat4("model", gameObject->transform->getTransformMatrix());
    this->sprite->render();
}

void Mayhem::ECS::Components::SpriteRenderer::UpdateSpriteAttributes() {
    this->sprite->color = color;
    this->sprite->regenVBOAttributes();
}

void DrawTriangle();
void CreateTriangle();
