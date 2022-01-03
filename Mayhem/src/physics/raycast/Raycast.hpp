#ifndef RAYCAST_H
#define RAYCAST_H

#include "../../math/vector/Vector3f.hpp"
#include "../../gameobject/GameObject.hpp"

#include "../../window/Window.hpp"

#define MAX_RAY_DISTANCE 1000.0f

namespace Mayhem {
    namespace Physics {
        class Raycast {
            private:
                Math::Vector3f origin, direction;
                float maxDistance;
                Math::Vector3f m_hit;
            public:
                Raycast(Math::Vector3f origin, Math::Vector3f direction, float maxDistance);
                Raycast(Math::Vector3f origin, Math::Vector3f direction);
                
                Math::Vector3f hit();
        };
    }
}

#endif /* ifndef RAYCAST_H */
