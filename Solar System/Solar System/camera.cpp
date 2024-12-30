#include "camera.h"

Camera::Camera() {
    
}

void Camera::initialize(glm::vec3 position, glm::vec3 up) {
    setPosition(position);
    WorldUp = up;
    updateCameraVectors();
    inputManager = &InputManager::getInstance();
    window = &Window::getInstance();
}

void Camera::initialize(float posX, float posY, float posZ, float upX, float upY, float upZ) {
    setPosition(glm::vec3(posX, posY, posZ));
    WorldUp = glm::vec3(upX, upY, upZ);
    updateCameraVectors();
    inputManager = &InputManager::getInstance();
}

Camera& Camera::getInstance() {
    static Camera instance;
    return instance;
}

glm::mat4 Camera::getProjectionMatrix() {
    return glm::perspective(glm::radians(FOV), (float)window->getWidth() / (float)window->getHeight(), NEAR, FAR);
}

glm::mat4 Camera::getViewMatrix() {
    return glm::lookAt(getPosition(), getPosition() + Front, Up);
}

void Camera::update(float deltaTime) {
    handleMovement(deltaTime);

    double xpos, ypos;
    inputManager->getMousePosition(xpos, ypos);
    static double lastX = window->getWidth() / 2.0f;
    static double lastY = window->getHeight() / 2.0f;
    static bool firstMouse = true;

    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    toggleCursorVisibility();

    if (glfwGetInputMode(window->getWindow(), GLFW_CURSOR) == GLFW_CURSOR_DISABLED) {
        float xOffset = xpos - lastX;
        float yOffset = lastY - ypos;
        lastX = xpos;
        lastY = ypos;

        processMouseMovement(xOffset, yOffset, true);
    }

    updateCameraVectors();
}


float scrollMultiplier;

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

void Camera::handleMovement(float deltaTime) {
    float velocity = SPEED * deltaTime * scrollMultiplier;

    glfwSetScrollCallback(window->getWindow(), scroll_callback);

    if (inputManager->getKey(GLFW_KEY_W))
        setPosition(getPosition() + Front * velocity);
    if (inputManager->getKey(GLFW_KEY_S))
        setPosition(getPosition() - Front * velocity);
    if (inputManager->getKey(GLFW_KEY_A))
        setPosition(getPosition() - Right * velocity);
    if (inputManager->getKey(GLFW_KEY_D))
        setPosition(getPosition() + Right * velocity);
    if (inputManager->getKey(GLFW_KEY_E))
        setPosition(getPosition() + WorldUp * velocity);
    if (inputManager->getKey(GLFW_KEY_Q))
        setPosition(getPosition() - WorldUp * velocity);
}

void Camera::toggleCursorVisibility() {
    static bool showCursor = false;
    if (inputManager->getKeyDown(GLFW_KEY_Z)) {
        showCursor = !showCursor;
        glfwSetInputMode(window->getWindow(), GLFW_CURSOR, showCursor ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_DISABLED);
        if (showCursor)
            glfwSetCursorPos(window->getWindow(), (float)window->getWidth() / 2.0f, (float)window->getHeight() / 2.0f);
    }
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

    setRotation(glm::vec3(Pitch, Yaw, 0.0f));
}