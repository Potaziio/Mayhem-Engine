#ifndef VECTOR2F_H
#define VECTOR2F_H

#include <iostream>
#include <cmath>
#include <math.h>

namespace Mayhem {
    namespace Math {
        struct Vector2f {
            float x;
            float y;

            Vector2f(float xPos, float yPos);
            Vector2f(float defVal);
            Vector2f();

            void Print();

            void Normalize();
            float getLength();

            static Vector2f Lerp(Vector2f source, Vector2f target, float speed);

            Vector2f operator-(Vector2f vecToSubstract);

            Vector2f operator+(Vector2f vecToAdd);

            Vector2f operator*(float val);
            Vector2f operator*(Vector2f vecToMult);

            void operator+=(Vector2f vecToAdd);
            void operator-=(Vector2f vecToSub);          
        };
    }
}

#endif /* ifndef VEC2F_H */
