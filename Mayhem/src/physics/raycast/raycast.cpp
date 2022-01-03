#include "Raycast.hpp"

Mayhem::Physics::Raycast::Raycast(Math::Vector3f origin, Math::Vector3f direction, float maxDistance): origin(origin), direction(direction) {
    glm::vec3 pointNdc = glm::vec3((2.0f * origin.x) / Window::getWidth() - 1.0f, -((2.0f * origin.y) / Window::getHeight() - 1.0f), 1.0f);

    // Ray pointing forwards (Z: -1.0f)
    glm::vec4 rayClip = glm::vec4(pointNdc.x, pointNdc.y, -1.0f, 1.0f);
    glm::vec4 rayEye = Window::getCurrentScene()->PerspectiveCamera->GetInvProjectionMatrix() * rayClip;
    rayEye = glm::vec4(rayEye.x, rayEye.y, -1.0f, 0.0f);
    glm::vec3 worldPos = (Window::getCurrentScene()->PerspectiveCamera->GetInvViewMatrix() * rayEye);
    worldPos = glm::normalize(worldPos);

    /* Vector3f(worldPos.x, worldPos.y, worldPos.z).Print(); */
}

// uses Maximum distance

Mayhem::Physics::Raycast::Raycast(Math::Vector3f position, Math::Vector3f direction) {
}
