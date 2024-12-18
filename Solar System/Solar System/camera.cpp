#include "camera.h"

Camera::Camera(glm::vec3 position, glm::vec3 up) {
    Position = position;
    WorldUp = up;
    updateCameraVectors();
}

Camera::Camera(float posX, float posY, float posZ, float upX, float upY, float upZ) {
    Position = glm::vec3(posX, posY, posZ);
    WorldUp = glm::vec3(upX, upY, upZ);
    updateCameraVectors();
}

glm::mat4 Camera::getProjectionMatrix(const int width, const int height) {
    return glm::perspective(glm::radians(FOV), (float)width / (float)height, NEAR, FAR);
}

glm::mat4 Camera::getViewMatrix() {
    return glm::lookAt(Position, Position + Front, Up);
}

void Camera::update(GLFWwindow* window, const int width, const int height, float deltaTime) {
    handleMovement(window, deltaTime);

    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);
    static double lastX = width / 2.0f;
    static double lastY = height / 2.0f;
    static bool firstMouse = true;

    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    toggleCursorVisibility(window, width, height);

    if (glfwGetInputMode(window, GLFW_CURSOR) == GLFW_CURSOR_DISABLED) {
        float xOffset = xpos - lastX;
        float yOffset = lastY - ypos;
        lastX = xpos;
        lastY = ypos;

        processMouseMovement(xOffset, yOffset, true);
    }
}

float scrollMultiplier = 1.0f;

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    if (yoffset > 0) {
        scrollMultiplier += 1.0f;
    } 
    if (yoffset < 0) {
        scrollMultiplier -= 1.0f;
    }
    scrollMultiplier = glm::clamp(scrollMultiplier, 0.0f, 100.0f);
}

void Camera::handleMovement(GLFWwindow* window, float deltaTime) {
    float velocity = SPEED * deltaTime * scrollMultiplier;

    glfwSetScrollCallback(window, scroll_callback);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        Position += Front * velocity;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        Position -= Front * velocity;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        Position -= Right * velocity;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        Position += Right * velocity;
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
        Position += WorldUp * velocity;
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        Position -= WorldUp * velocity;
}

void Camera::toggleCursorVisibility(GLFWwindow* window, int width, int height) {
    static bool showCursor = false;

    static bool wasZPressed = false;
    bool zPressed = glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS;
    if (zPressed && !wasZPressed) {
        showCursor = !showCursor;
        glfwSetInputMode(window, GLFW_CURSOR, showCursor ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_DISABLED);
        if (showCursor)
            glfwSetCursorPos(window, width / 2.0, height / 2.0);
    }
    wasZPressed = zPressed;
}

void Camera::processMouseMovement(float xOffset, float yOffset, bool constrainPitch) {
    xOffset *= SENSITIVITY;
    yOffset *= SENSITIVITY;

    Yaw += xOffset;
    Pitch += yOffset;

    if (constrainPitch) {
        Pitch = glm::clamp(Pitch, -89.0f, 89.0f);
    }

    updateCameraVectors();
}

void Camera::updateCameraVectors() {
    glm::vec3 front;
    front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    front.y = sin(glm::radians(Pitch));
    front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    Front = glm::normalize(front);
    Right = glm::normalize(glm::cross(Front, WorldUp));
    Up = glm::normalize(glm::cross(Right, Front));
}