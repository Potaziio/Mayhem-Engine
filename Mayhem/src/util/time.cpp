#include "Time.hpp"

Mayhem::Utils::Time::Time() {
    endTime = GetMilliseconds();
    dt = endTime - startTime;
    startTime = endTime;
}

float Mayhem::Utils::Time::GetMilliseconds() {
    return (float)glfwGetTime();
}

float Mayhem::Utils::Time::deltaTime() {
    return dt;
}

float Mayhem::Utils::Time::startTime = Mayhem::Utils::Time::GetMilliseconds();
float Mayhem::Utils::Time::endTime = Mayhem::Utils::Time::GetMilliseconds();
float Mayhem::Utils::Time::dt = -1.0f;
