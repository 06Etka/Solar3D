#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>


#include <glm/glm.hpp>

#include "window.h"
#include "camera.h"
#include "shader.h"
#include "planet.h"

const float SKYBOX_COLOR[3] = { 0.0f, 0.05f, 0.1f };

float deltaTime;
float lastTime;

Planet createPlanet(Camera& camera, const std::string& shaderName, const std::string& texturePath,
	const glm::vec3& scale, const glm::vec3& position) 
{
	Planet planet(camera, shaderName, texturePath);
	planet.setScale(scale);
	planet.setPosition(position);
	return planet;
}

int main() {
	Window window;
    Camera camera(glm::vec3(0.0f, 0.0f, 500.0f), glm::vec3(0.0f, 1.0f, 0.0f), window);

	std::vector<Planet> planets = {
		createPlanet(camera, "planet", "assets/sun.png", glm::vec3(139.2f), glm::vec3(0.0f)),
		createPlanet(camera, "planet", "assets/mercury.png", glm::vec3(0.4879f), glm::vec3(579.0f, 0.0f, 0.0f)),
		createPlanet(camera, "planet", "assets/venus.png", glm::vec3(1.2104f), glm::vec3(1082.0f, 0.0f, 0.0f)),
		createPlanet(camera, "planet", "assets/earth.png", glm::vec3(1.2756f), glm::vec3(1496.0f, 0.0f, 0.0f)),
		createPlanet(camera, "planet", "assets/mars.png", glm::vec3(0.6779f), glm::vec3(2279.0f, 0.0f, 0.0f)),
		createPlanet(camera, "planet", "assets/jupiter.png", glm::vec3(14.2984f), glm::vec3(7786.0f, 0.0f, 0.0f)),
		createPlanet(camera, "planet", "assets/saturn.png", glm::vec3(12.0f), glm::vec3(14335.0f, 0.0f, 0.0f)),
		createPlanet(camera, "planet", "assets/uranus.png", glm::vec3(5.1118f), glm::vec3(28725.0f, 0.0f, 0.0f)),
		createPlanet(camera, "planet", "assets/neptune.png", glm::vec3(4.9244f), glm::vec3(44951.0f, 0.0f, 0.0f)),
	};

    glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);
	glFrontFace(GL_CW);

	while (!glfwWindowShouldClose(window.getWindow()))
	{
		float currentTime = glfwGetTime();
		deltaTime = currentTime - lastTime;
		lastTime = currentTime;

		glClearColor(SKYBOX_COLOR[0], SKYBOX_COLOR[1], SKYBOX_COLOR[2], 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		camera.update(deltaTime);
        glm::mat4 proj = camera.getProjectionMatrix();
        glm::mat4 view = camera.getViewMatrix();

		for (auto& planet : planets) {
			planet.update(deltaTime);
		}

		glfwPollEvents();
		glfwSwapBuffers(window.getWindow());
	}

	return 0;
}