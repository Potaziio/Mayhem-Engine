#ifndef MATHUTILS_H
#define MATHUTILS_H

#include <iostream>
#include <cmath>

namespace Mayhem {
    namespace Math {
        struct Utils {
            static float randFloat(float min, float max);
            static int randInt(int min, int max);

            static void clampF(float* val, float min, float max);
            static void clampI(int* val, int min, int max);
        };        
    }
}


#endif /* ifndef MATHUTILS_H */
