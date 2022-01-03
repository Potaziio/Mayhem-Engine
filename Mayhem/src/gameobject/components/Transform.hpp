#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "../../util/MayhemUtil.hpp"
#include "../../math/vector/Vector3f.hpp"

#include "Component.hpp"

#include "../../../../include/vendor/glm/glm/glm.hpp"
#include "../../../../include/vendor/glm/glm/gtc/matrix_transform.hpp"
#include "../../../../include/vendor/glm/glm/gtc/type_ptr.hpp"
#include "../../../../include/vendor/glm/glm/gtx/string_cast.hpp"

namespace Mayhem {
    namespace ECS {
        // Forward declaration
        class GameObject;

        namespace Components {
            class Transform : public Component {
                private:
                    glm::mat4 transformMatrix;
                    Utils::UUID componentID; 
                public:
                    std::string GetComponentType() override {return "Transform";}

                    void OnImGui() override;

                    GameObject* gameObject;
                    Math::Vector3f position;
                    Math::Vector3f scale;
                    Math::Vector3f rotation;

                    Transform(Math::Vector3f position, Math::Vector3f scale, Math::Vector3f rotation);

                    Utils::UUID getID() {return componentID;}
                    glm::mat4 getTransformMatrix(); 
            };
        }
    }
}

#endif /* ifndef TRANSFORM_H */
