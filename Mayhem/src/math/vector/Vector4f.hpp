#ifndef VECTOR4F_H
#define VECTOR4F_H

#include <iostream>
#include <cmath>
#include <math.h>

namespace Mayhem {
    namespace Math {
        struct Vector4f {
            float x;
            float y;
            float z;
            float w;

            Vector4f(float xPos, float yPos, float zPos, float wPos);
            Vector4f();

            void Print();

            void Normalize();
            float getLength();

            bool operator==(Vector4f vecToCompare);
            bool operator!=(Vector4f vecToCompare);


            Vector4f operator-(Vector4f vecToSubstract);

            Vector4f operator*(float val);
            Vector4f operator*(Vector4f vecToMult);

            void operator+=(Vector4f vecToAdd);
            void operator-=(Vector4f vecToSub);          
        };
    }
}

#endif /* ifndef VECTOR4F_H */
