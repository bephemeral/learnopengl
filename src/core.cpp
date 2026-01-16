#include "core.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

float getDeltaTime() {
    static float lastFrame{ 0.0f };

    const float currentFrame{ static_cast<float>(glfwGetTime()) };  
    const float deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    return deltaTime;
}