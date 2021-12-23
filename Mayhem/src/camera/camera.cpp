#include "Camera.hpp"

// Ortho Camera

Mayhem::ECS::OrthographicCamera::OrthographicCamera(Math::Vector3f pos, float xMin, float xMax, float yMin, float yMax, float zMin, float zMax)
    : xMin(xMin), xMax(xMax), yMin(yMin), yMax(yMax), zMin(zMin), zMax(zMax), Mayhem::ECS::GameObject("Orthographic Camera") 
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
            viewMatrix, 
            projectionMatrix, glm::vec4(0.0f, 0.0f, CameraBoundsX, CameraBoundsY));

    return Math::Vector3f(pos.x, -pos.y, pos.z);
}

Mayhem::Math::Vector2f Mayhem::ECS::OrthographicCamera::ScreenToWorldPoint(Mayhem::Math::Vector2f point) {
    glm::vec3 pos = glm::unProject(glm::vec3(point.x, point.y, 0.0f), 
            viewMatrix, 
            projectionMatrix, glm::vec4(0.0f, 0.0f, CameraBoundsX, CameraBoundsY));

    return Math::Vector2f(pos.x, -pos.y);
}

void Mayhem::ECS::OrthographicCamera::update() {
    Math::Vector3f pos = transform->position;

    viewMatrix = glm::mat4(1.0f);
    viewMatrix = glm::lookAt(glm::vec3(pos.x, pos.y, pos.z), cameraFront + glm::vec3(pos.x, pos.y, pos.z), cameraUp);

    projectionMatrix = glm::mat4(1.0f);
    projectionMatrix = glm::ortho(xMin, xMax, yMin, yMax, zMin, zMax);
}

glm::mat4 Mayhem::ECS::OrthographicCamera::GetViewMatrix() {
    return viewMatrix;
}

glm::mat4 Mayhem::ECS::OrthographicCamera::GetProjectionMatrix() {
    return projectionMatrix;
}


// Projection Camera

Mayhem::ECS::PerspectiveCamera::PerspectiveCamera(Math::Vector3f pos, float fov, float x, float y, float near, float far)
    : fov(fov), aspectX(x), aspectY(y), near(near), far(far), GameObject("Perspective Camera") 
{
    this->transform->position = pos;

    inverseViewMatrix = glm::mat4(1.0f);
    inverseProjectionMatrix = glm::mat4(1.0f);

    viewMatrix = glm::mat4(1.0f);
    viewMatrix = viewMatrix = glm::lookAt(glm::vec3(pos.x, pos.y, pos.z), cameraFront + glm::vec3(pos.x, pos.y, pos.z), cameraUp);

    projectionMatrix = glm::mat4(1.0f);
    projectionMatrix = projectionMatrix = glm::perspective(glm::radians(fov), x / y, 0.1f, 100.0f);

}

void Mayhem::ECS::PerspectiveCamera::update() {
    Math::Vector3f pos = transform->position;

    viewMatrix = glm::mat4(1.0f);
    viewMatrix = glm::lookAt(glm::vec3(pos.x, pos.y, pos.z), cameraFront + glm::vec3(pos.x, pos.y, pos.z), cameraUp);

    projectionMatrix = glm::mat4(1.0f);
    projectionMatrix = glm::perspective(glm::radians(fov), aspectX / aspectY, 0.1f, 100.0f);

    inverseViewMatrix = glm::inverse(viewMatrix);
    inverseProjectionMatrix = glm::inverse(projectionMatrix);
}

Mayhem::Math::Vector3f Mayhem::ECS::PerspectiveCamera::ScreenPointToRay(Mayhem::Math::Vector3f point) {
    glm::vec4 viewport = glm::vec4(0.0f, 0.0f, aspectX, aspectY);
    glm::vec3 pos = glm::vec3(point.x, point.y - 0.5, 0.5f);

    glm::vec3 temp = glm::unProject(pos, viewMatrix, projectionMatrix, viewport);

    return Math::Vector3f(temp.x, -temp.y, temp.z) * 100.0f;
}

glm::mat4 Mayhem::ECS::PerspectiveCamera::GetViewMatrix() {
    return viewMatrix;
}

glm::mat4 Mayhem::ECS::PerspectiveCamera::GetInvViewMatrix() {
    return this->inverseViewMatrix;
}

glm::mat4 Mayhem::ECS::PerspectiveCamera::GetInvProjectionMatrix() {
    return this->inverseProjectionMatrix;
}

glm::mat4 Mayhem::ECS::PerspectiveCamera::GetProjectionMatrix() {
    return projectionMatrix;
}
