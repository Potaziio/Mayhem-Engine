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
    CameraBoundsX = xMax;
    CameraBoundsY = yMax;

    this->xMin = xMin;
    this->xMax = xMax;
    this->yMin = yMin;
    this->yMax = yMax;
    this->zMin = zMin;
    this->zMax = zMax;
}

Mayhem::Math::Vector3f Mayhem::ECS::OrthographicCamera::ScreenToWorldPoint(Mayhem::Math::Vector3f point) {
    glm::vec3 pos = glm::unProject(glm::vec3(point.x, point.y, point.z), 
            glm::mat4(1.0f), 
            this->GetProjectionMatrix(), glm::vec4(0.0f, 0.0f, CameraBoundsX, CameraBoundsY));

    return Math::Vector3f(pos.x, pos.y, pos.z);
}

Mayhem::Math::Vector2f Mayhem::ECS::OrthographicCamera::ScreenToWorldPoint(Mayhem::Math::Vector2f point) {
    glm::vec3 pos = glm::unProject(glm::vec3(point.x, point.y, 0.0f), 
            glm::mat4(1.0f), 
            this->GetProjectionMatrix(), glm::vec4(0.0f, 0.0f, CameraBoundsX, CameraBoundsY));

    return Math::Vector2f(pos.x, pos.y);
}

void Mayhem::ECS::OrthographicCamera::update() {
    Math::Vector3f pos = transform->position;

    viewMatrix = glm::mat4(1.0f);
    viewMatrix = glm::lookAt(glm::vec3(pos.x, -pos.y, pos.z), cameraFront + glm::vec3(pos.x, -pos.y, pos.z), cameraUp);

    projectionMatrix = glm::mat4(1.0f);
    projectionMatrix = glm::ortho(xMin, xMax, yMin, yMax, zMin, zMax);
}

glm::mat4 Mayhem::ECS::OrthographicCamera::GetViewMatrix() {
    return viewMatrix;
}

glm::mat4 Mayhem::ECS::OrthographicCamera::GetProjectionMatrix() {
    return projectionMatrix;
}
