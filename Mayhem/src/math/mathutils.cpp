#include "MathUtils.hpp"

float Mayhem::Math::Utils::randFloat(float min, float max) {
    return ((max - min) * ((float)rand() / (float)RAND_MAX)) + min;
}

int Mayhem::Math::Utils::randInt(int min, int max) {
    return min + rand() / (RAND_MAX / (max - min + 1) + 1);
}

void Mayhem::Math::Utils::clampF(float* val, float min, float max) {

}

void Mayhem::Math::Utils::clampI(int* val, int min, int max) {

}
