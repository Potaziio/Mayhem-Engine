#ifndef CAMERA_H
#define CAMERA_H


#include "../util/MayhemUtil.hpp"
#include "../math/vector/Vector2f.hpp"
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
                float xMin;
                float xMax;
                float yMin;
                float yMax;
                float zMin;
                float zMax;

                OrthographicCamera(Math::Vector3f pos, float xMin, float xMax, float yMin, float yMax, float zMin, float zMax);

                glm::mat4 GetViewMatrix();
                glm::mat4 GetProjectionMatrix();
        };

        class PerspectiveCamera : public GameObject {

        };
    }
}


#endif /* ifndef CAMERA_H */
