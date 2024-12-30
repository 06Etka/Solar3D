#ifndef CAMERA_H
#define CAMERA_H

#include <iostream>

#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "window.h"
#include "transform.h"
#include "input_manager.h"

class Camera : public Transform
{
public:
    glm::vec3 Position;
    glm::vec3 Front;
    glm::vec3 Up;
    glm::vec3 Right;
    glm::vec3 WorldUp;

    float Yaw = -90.0f;
    float Pitch = 0.0f;

    const float SPEED = 2.5f;
    const float SENSITIVITY = 0.1f;
    const float FOV = 60.0f;
    const float NEAR = 0.01f;
    const float FAR = 1000000.0f;

    static Camera& getInstance();

    void initialize(glm::vec3 position, glm::vec3 up);
    void initialize(float posX, float posY, float posZ, float upX, float upY, float upZ);

    glm::mat4 getProjectionMatrix();
    glm::mat4 getViewMatrix();

    void update(float deltaTime);

private:
    Camera();

    Camera(const Camera&) = delete;
    Camera& operator=(const Camera&) = delete;

    void updateCameraVectors();

    void processMouseMovement(float xOffset, float yOffset, bool constrainPitch);
    void handleMovement(float deltaTime);
    void toggleCursorVisibility();

    Window* window;
    InputManager* inputManager;
};

#endif // !CAMERA_H