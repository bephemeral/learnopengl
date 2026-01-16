#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class Camera {
public:
    Camera();

    static void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
        Camera* cam = static_cast<Camera*>(glfwGetWindowUserPointer(window));
        if(cam) {
            cam->processMouse(window, xpos, ypos);
        }
    }
    void processMovement(GLFWwindow* window);
    glm::mat4 getViewMatrix() const;
private:
    static inline constexpr glm::vec3 CAMERA_UP{ 0.0f, 1.0f,  0.0f };
    static inline constexpr float CAMERA_SPEED{ 5.0f };

    glm::vec3 cameraPos{ 0.0f, 0.0f, 3.0f };
    glm::vec3 cameraFront{ 0.0f, 0.0f, -1.0f };

    float yaw { -90.0f }, pitch { 0.0f };

    void processMouse(GLFWwindow* window, double xpos, double ypos);
};

