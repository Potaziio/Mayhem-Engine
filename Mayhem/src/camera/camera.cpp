#include "Camera.hpp"

Mayhem::ECS::OrthographicCamera::OrthographicCamera(Math::Vector3f pos, float xMin, float xMax, float yMin, float yMax, float zMin, float zMax)
    : xMin(xMin), xMax(xMax), yMin(yMin), yMax(yMax), zMin(zMin), zMax(zMax), Mayhem::ECS::GameObject("Camera") 
{
    this->transform->position = pos;     

    projectionMatrix = glm::mat4(1.0f);
    projectionMatrix = glm::ortho(xMin, xMax, yMin, yMax, zMin, zMax);

    viewMatrix = glm::mat4(1.0f);
    viewMatrix = glm::lookAt(glm::vec3(pos.x, pos.y, pos.z), cameraFront + glm::vec3(pos.x, pos.y, pos.z), cameraUp);
}

void Mayhem::ECS::OrthographicCamera::UpdateOrthoCameraBounds(float xMin, float xMax, float yMin, float yMax, float zMin, float zMax) {
    this->xMin = xMin;
    this->xMax = xMax;
    this->yMin = yMin;
    this->yMax = yMax;
    this->zMin = zMin;
    this->zMax = zMax;
}

glm::mat4 Mayhem::ECS::OrthographicCamera::GetViewMatrix() {
    Math::Vector3f pos = transform->position;

    viewMatrix = glm::mat4(1.0f);
    viewMatrix = glm::lookAt(glm::vec3(pos.x, pos.y, pos.z), cameraFront + glm::vec3(pos.x, pos.y, pos.z), cameraUp);

    return viewMatrix;
}

glm::mat4 Mayhem::ECS::OrthographicCamera::GetProjectionMatrix() {
    projectionMatrix = glm::mat4(1.0f);
    projectionMatrix = glm::ortho(xMin, xMax, yMin, yMax, zMin, zMax);

    return projectionMatrix;
}
