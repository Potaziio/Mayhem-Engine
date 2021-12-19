#include "Vector2f.hpp"

Mayhem::Math::Vector2f::Vector2f(float xPos, float yPos) :x(xPos), y(yPos) {}
Mayhem::Math::Vector2f::Vector2f() :x(0.0f), y(0.0f) {}

void Mayhem::Math::Vector2f::Print() {
    std::cout << x << ", " << y << std::endl;
}

Mayhem::Math::Vector2f Mayhem::Math::Vector2f::operator-(Vector2f vecToSubstract) {
    return Vector2f(x - vecToSubstract.x, y - vecToSubstract.y);
}  

Mayhem::Math::Vector2f Mayhem::Math::Vector2f::operator*(float val) {
    return Vector2f(x * val, y * val);
}

Mayhem::Math::Vector2f Mayhem::Math::Vector2f::operator*(Vector2f vecToMult) {
    return Vector2f(x * vecToMult.x, y * vecToMult.y);
}

float Mayhem::Math::Vector2f::getLength() {
    return sqrt(x * x + y * y);
}

void Mayhem::Math::Vector2f::Normalize() {
    float mag = getLength();

    if (mag > 0) {
        x /= mag;
        y /= mag;
    }    
}

void Mayhem::Math::Vector2f::operator+=(Vector2f vecToAdd) {
    x += vecToAdd.x;
    y += vecToAdd.y;
}

void Mayhem::Math::Vector2f::operator-=(Vector2f vecToSub) {
    x -= vecToSub.x;
    y -= vecToSub.y;
}
