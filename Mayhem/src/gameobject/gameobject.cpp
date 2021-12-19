#include "GameObject.hpp"

Mayhem::ECS::GameObject::GameObject(std::string name): name(name), uuid(Mayhem::Utils::UUID()) {
    printf("Created GameObject -> : %s UUID: %s\n", this->name.c_str(), this->uuid.id().c_str());

    transform->scale = Math::Vector3f(50.0f, 50.0f,  50.0f);
    this->components[typeid(Components::Transform)] = transform;
}

Mayhem::ECS::GameObject::GameObject(std::string name, Components::Transform transform): name(name), uuid(Mayhem::Utils::UUID()) {
    printf("Created GameObject -> : %s UUID: %s\n", this->name.c_str(), this->uuid.id().c_str());

    this->transform->position = transform.position;
    this->transform->scale = transform.scale;

    this->components[typeid(Components::Transform)] = this->transform;
}

std::unordered_map<std::type_index, Mayhem::ECS::Components::Component*> Mayhem::ECS::GameObject::GetComponents() {
    return this->components;
}
