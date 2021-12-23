#include "Transform.hpp"

Mayhem::ECS::Components::Transform::Transform(Math::Vector3f position, Math::Vector3f scale, Math::Vector3f rotation): position(position), scale(scale), rotation(rotation), componentID(Utils::UUID()) {}

glm::mat4 Mayhem::ECS::Components::Transform::getTransformMatrix() {
    transformMatrix = glm::mat4(1.0f);
    transformMatrix = glm::translate(transformMatrix, glm::vec3(position.x, position.y, position.z));
    transformMatrix = glm::scale(transformMatrix, glm::vec3(scale.x, scale.y, scale.z));
    /* transformMatrix = glm::rotate(transformMatrix, glm::radians(90.0f), glm::vec3(rotation.x, rotation.y, rotation.z)); */

    return transformMatrix;
}
