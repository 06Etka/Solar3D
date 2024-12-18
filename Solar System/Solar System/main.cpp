#include <vector>


#include <glm/glm.hpp>

#include "window.h"
#include "camera.h"
#include "shader.h"
#include "planet.h"

const float SKYBOX_COLOR[3] = { 0.0f, 0.05f, 0.1f };

float deltaTime;
float lastTime;

int main() {
	Window window;
    Camera camera(glm::vec3(0.0f, 0.0f, 500.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	
	Planet sun(139.2000f, "assets/sun.png", glm::vec3(0.0f, 0.0f, 0.0f));
	Planet mercury(0.4879f, "assets/mercury.png", glm::vec3(579.0f / 1.2f, 0.0f, 0.0f));
	Planet venus(1.2104f, "assets/venus.png", glm::vec3(1082.0f / 1.2f, 0.0f, 0.0f));
	Planet earth(1.2756f, "assets/earth.png", glm::vec3(1496.0f / 1.2f, 0.0f, 0.0f));
	Planet mars(0.6779f, "assets/mars.png", glm::vec3(2279.0f / 1.2f, 0.0f, 0.0f));
	Planet jupiter(14.2984f, "assets/jupiter.png", glm::vec3(7786.0f / 1.2f, 0.0f, 0.0f));
	Planet saturn(12.0000f, "assets/saturn.png", glm::vec3(14335.0f / 1.2f, 0.0f, 0.0f));
	Planet uranus(5.1118f, "assets/uranus.png", glm::vec3(28725.0f / 1.2f, 0.0f, 0.0f));
	Planet neptune(4.9244f, "assets/neptune.png", glm::vec3(44951.0f / 1.2f, 0.0f, 0.0f));

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

		camera.update(window.getWindow(), window.getWidth(), window.getHeight(), deltaTime);
        glm::mat4 proj = camera.getProjectionMatrix(window.getWidth(), window.getHeight());
        glm::mat4 view = camera.getViewMatrix();

		sun.draw(proj, view, camera.Position);
		mercury.draw(proj, view, camera.Position);
		venus.draw(proj, view, camera.Position);
		earth.draw(proj, view, camera.Position);
		mars.draw(proj, view, camera.Position);
		jupiter.draw(proj, view, camera.Position);
		saturn.draw(proj, view, camera.Position);
		uranus.draw(proj, view, camera.Position);
		neptune.draw(proj, view, camera.Position);

		glfwPollEvents();
		glfwSwapBuffers(window.getWindow());
	}

	return 0;
}