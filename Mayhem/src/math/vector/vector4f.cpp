#include "Vector4f.hpp"

Mayhem::Math::Vector4f::Vector4f(float xPos, float yPos, float zPos, float wPos) :x(xPos), y(yPos), z(zPos), w(wPos) {}
Mayhem::Math::Vector4f::Vector4f() :x(0.0f), y(0.0f), z(0.0f) {}

void Mayhem::Math::Vector4f::Print() {
    std::cout << x << ", " << y << ", " << z << ", " << w <<  std::endl;
} 

Mayhem::Math::Vector4f Mayhem::Math::Vector4f::operator-(Vector4f vecToSubstract) {
    return Vector4f(x - vecToSubstract.x, y - vecToSubstract.y, z - vecToSubstract.z, z - vecToSubstract.w);
}  

Mayhem::Math::Vector4f Mayhem::Math::Vector4f::operator*(float val) {
    return Vector4f(x * val, y * val, z * val, w * val);
}

Mayhem::Math::Vector4f Mayhem::Math::Vector4f::operator*(Vector4f vecToMult) {
    return Vector4f(x * vecToMult.x, y * vecToMult.y, z * vecToMult.z, w * vecToMult.w);
}

float Mayhem::Math::Vector4f::getLength() {
    return sqrt(x * x + y * y + z * z + w * w);
}

void Mayhem::Math::Vector4f::Normalize() {
    float mag = getLength();

    if (mag > 0) {
        x /= mag;
        y /= mag;
        z /= mag;
        w /= mag;
    }    
}

void Mayhem::Math::Vector4f::operator+=(Vector4f vecToAdd) {
    x += vecToAdd.x;
    y += vecToAdd.y;
    z += vecToAdd.z;
    w += vecToAdd.w;
}

void Mayhem::Math::Vector4f::operator-=(Vector4f vecToSub) {
    x -= vecToSub.x;
    y -= vecToSub.y;
    z -= vecToSub.z;
    w -= vecToSub.w;
}

