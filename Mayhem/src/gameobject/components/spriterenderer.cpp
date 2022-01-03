#include "SpriteRenderer.hpp"
#include "Component.hpp"

void Mayhem::ECS::Components::SpriteRenderer::render() {
    if (this->color * 10 != this->sprite->color * 10) {
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
    this->sprite->color = color * 10;
    this->sprite->regenVBOAttributes();
}

void Mayhem::ECS::Components::SpriteRenderer::OnImGui() {
    ImGui::ColorEdit4("Color", (float*)&this->color);
}

void DrawTriangle();
void CreateTriangle();
