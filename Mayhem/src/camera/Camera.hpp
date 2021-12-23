#ifndef CAMERA_H
#define CAMERA_H


#include "../util/MayhemUtil.hpp"
#include "../math/vector/Vector2f.hpp"
#include "../math/vector/Vector3f.hpp"
#include "../math/vector/Vector4f.hpp"
#include "../gameobject/GameObject.hpp"

#include "../../../../include/vendor/glm/glm/glm.hpp"
#include "../../../../include/vendor/glm/glm/gtc/matrix_transform.hpp"
#include "../../../../include/vendor/glm/glm/gtc/type_ptr.hpp"
#include "../../../../include/vendor/glm/glm/gtx/string_cast.hpp"

namespace Mayhem {
    namespace ECS {
        class OrthographicCamera : public GameObject {
            private:
                glm::mat4 viewMatrix, projectionMatrix;
                glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
                glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
            public:
                float CameraBoundsX;
                float CameraBoundsY;

                float CameraFrustum;

                float xMin;
                float xMax;
                float yMin;
                float yMax;
                float zMin;
                float zMax;

                OrthographicCamera(Math::Vector3f pos, float xMin, float xMax, float yMin, float yMax, float zMin, float zMax);

                Math::Vector3f ScreenToWorldPoint(Math::Vector3f point);
                Math::Vector2f ScreenToWorldPoint(Math::Vector2f point);

                void UpdateOrthoCameraBounds(float xMin, float xMax, float yMin, float yMax, float zMin, float zMax);

                glm::mat4 GetViewMatrix();
                glm::mat4 GetProjectionMatrix();

                void update();
        };

        class PerspectiveCamera : public GameObject {
            private:
                glm::mat4 viewMatrix, projectionMatrix, inverseProjectionMatrix, inverseViewMatrix;
                glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
                glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f,  -1.0f);
            public:
                float fov;

                float aspectX;
                float aspectY;

                float near;
                float far;

                PerspectiveCamera(Math::Vector3f pos, float fov, float x, float y, float near, float far);

                Math::Vector3f ScreenPointToRay(Math::Vector3f point);

                glm::mat4 GetInvViewMatrix();
                glm::mat4 GetInvProjectionMatrix();
                glm::mat4 GetViewMatrix();
                glm::mat4 GetProjectionMatrix();

                void update();
        };
    }
}


#endif /* ifndef CAMERA_H */
