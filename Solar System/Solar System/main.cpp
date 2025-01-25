#include <iostream>
#include <string>
#include <vector>

#include <glm/glm.hpp>

#include "window.h"
#include "camera.h"
#include "shader.h"
#include "input_manager.h"
#include "skybox.h"
#include "solar_system.h"

const float SKYBOX_COLOR[3] = { 1.0f, 1.0f, 1.0f };

float deltaTime;
float lastTime;

int main() {
	Window::getInstance().initialize();
	Camera::getInstance().initialize(glm::vec3(0.0f, 0.0f, 50.0), glm::vec3(0.0f, 1.0f, 0.0f));
	InputManager::getInstance().initialize();
	Skybox skybox;

	SolarSystem solarSystem;

    glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);
    glFrontFace(GL_CW);

	while (!glfwWindowShouldClose(Window::getInstance().getWindow()))
	{
		float currentTime = glfwGetTime();
		deltaTime = currentTime - lastTime;
		lastTime = currentTime;

		if (InputManager::getInstance().getKeyDown(GLFW_KEY_1)) {
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}
		if (InputManager::getInstance().getKeyDown(GLFW_KEY_2)) {
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}

		glClearColor(SKYBOX_COLOR[0], SKYBOX_COLOR[1], SKYBOX_COLOR[2], 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		Camera::getInstance().update(deltaTime);

		solarSystem.update(deltaTime);
		solarSystem.render();

		skybox.render();

		glfwPollEvents();
		glfwSwapBuffers(Window::getInstance().getWindow());
	}

	return 0;
}