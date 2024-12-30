#include "input_manager.h"

#include <unordered_map>

InputManager::InputManager() : window(nullptr)
{
}

void InputManager::initialize() {
    window = &Window::getInstance();
}

InputManager& InputManager::getInstance() {
	static InputManager instance;
	return instance;
}

bool InputManager::getKey(int key) {
    return glfwGetKey(window->getWindow(), key) == GLFW_PRESS;
}

std::unordered_map<int, bool> prevDownKeyStates;
bool InputManager::getKeyDown(int key) {
    int currentState = glfwGetKey(window->getWindow(), key);

    bool wasPressedLastFrame = prevDownKeyStates[key];

    prevDownKeyStates[key] = currentState == GLFW_PRESS;

    return !wasPressedLastFrame && currentState == GLFW_PRESS;
}

std::unordered_map<int, bool> prevUpKeyStates;
bool InputManager::getKeyUp(int key) {
    int currentState = glfwGetKey(window->getWindow(), key);

    bool wasPressedLastFrame = prevUpKeyStates[key];

    prevUpKeyStates[key] = currentState == GLFW_RELEASE;

    return !wasPressedLastFrame && currentState == GLFW_RELEASE;
}

void InputManager::getMousePosition(double& xPos, double& yPos) {
	glfwGetCursorPos(window->getWindow(), &xPos, &yPos);
}