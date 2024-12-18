#ifndef CAMERA_H
#define CAMERA_H

#include <iostream>

#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera
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

    Camera(glm::vec3 position, glm::vec3 up);
    Camera(float posX, float posY, float posZ, float upX, float upY, float upZ);

    glm::mat4 getProjectionMatrix(const int width, const int height);
    glm::mat4 getViewMatrix();

	void update(GLFWwindow* window, const int width, const int height, float deltaTime);

private:
    void updateCameraVectors();

    void processMouseMovement(float xOffset, float yOffset, bool constrainPitch);
    void handleMovement(GLFWwindow* window, float deltaTime);
    void toggleCursorVisibility(GLFWwindow* window, int width, int height);
};

#endif // !CAMERA_H
