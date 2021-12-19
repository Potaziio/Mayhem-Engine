#include "Vector3f.hpp"

Mayhem::Math::Vector3f::Vector3f(float xPos, float yPos, float zPos) :x(xPos), y(yPos), z(zPos) {}
Mayhem::Math::Vector3f::Vector3f(Vector2f vec, float zPos): x(vec.x), y(vec.y), z(zPos) {}

Mayhem::Math::Vector3f::Vector3f() :x(0.0f), y(0.0f), z(0.0f) {}

void Mayhem::Math::Vector3f::Print() {
    std::cout << x << ", " << y << ", " << z << std::endl;
}

Mayhem::Math::Vector3f Mayhem::Math::Vector3f::operator-(Vector3f vecToSubstract) {
    return Vector3f(x - vecToSubstract.x, y - vecToSubstract.y, z - vecToSubstract.z);
}  

Mayhem::Math::Vector3f Mayhem::Math::Vector3f::operator*(float val) {
    return Vector3f(x * val, y * val, z * val);
}

Mayhem::Math::Vector3f Mayhem::Math::Vector3f::operator*(Vector3f vecToMult) {
    return Vector3f(x * vecToMult.x, y * vecToMult.y, z * vecToMult.z);
}

float Mayhem::Math::Vector3f::getLength() {
    return sqrt(x * x + y * y + z * z);
}

void Mayhem::Math::Vector3f::Normalize() {
    float mag = getLength();

    if (mag > 0) {
        x /= mag;
        y /= mag;
        z /= mag;
    }    
}

void Mayhem::Math::Vector3f::operator+=(Vector3f vecToAdd) {
    x += vecToAdd.x;
    y += vecToAdd.y;
    z += vecToAdd.z;
}

void Mayhem::Math::Vector3f::operator-=(Vector3f vecToSub) {
    x -= vecToSub.x;
    y -= vecToSub.y;
    z -= vecToSub.z;
}
