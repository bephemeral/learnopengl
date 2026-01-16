#include "camera.h"
#include "core.h"  
#include <glm/ext/matrix_transform.hpp>

Camera::Camera() = default;

void Camera::processMovement(GLFWwindow* window) {
    const float cameraSpeed = CAMERA_SPEED * getDeltaTime();
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cameraPos += cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cameraPos -= cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cameraPos -= glm::normalize(glm::cross(cameraFront, CAMERA_UP)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cameraPos += glm::normalize(glm::cross(cameraFront, CAMERA_UP)) * cameraSpeed;
}

void Camera::processMouse(GLFWwindow* window, double xpos, double ypos) {
    static bool firstMouse{ true };
    static float lastX{ 800.0f / 2.0f };
    static float lastY{ 600.0f / 2.0f };

    if (firstMouse) {
        lastX = static_cast<float>(xpos);
        lastY = static_cast<float>(ypos);
        firstMouse = false;
    }

    float xoffset = static_cast<float>(xpos) - lastX;
    float yoffset = lastY - static_cast<float>(ypos); // reversed since y-coordinates go from bottom to top
    lastX = static_cast<float>(xpos);
    lastY = static_cast<float>(ypos);

    const float sensitivity{ 0.1f };
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw   += xoffset;
    pitch += yoffset;

    if(pitch > 89.0f)
        pitch = 89.0f;
    if(pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(front);
}

glm::mat4 Camera::getViewMatrix() const {
    return glm::lookAt(cameraPos, cameraPos + cameraFront, CAMERA_UP);
}