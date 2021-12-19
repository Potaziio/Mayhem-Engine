#ifndef VECTOR3F_H
#define VECTOR3F_H

#include <iostream>
#include <cmath>
#include <math.h>

#include "Vector2f.hpp"

namespace Mayhem {
    namespace Math {
        struct Vector3f {
            float x;
            float y;
            float z;

            Vector3f(float xPos, float yPos, float zPos);
            Vector3f(Vector2f vec, float zPos);
            Vector3f();

            void Print();

            void Normalize();
            float getLength();

            Vector3f operator-(Vector3f vecToSubstract);

            Vector3f operator*(float val);
            Vector3f operator*(Vector3f vecToMult);

            void operator+=(Vector3f vecToAdd);
            void operator-=(Vector3f vecToSub);          
        };
    }
}

#endif /* ifndef VECTOR4F_H */
