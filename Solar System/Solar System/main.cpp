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
	
	std::string sunTexturePath = "assets/sun.png";
	Planet sun(139.2000f, sunTexturePath);

	std::string mercuryTexturePath = "assets/mercury.png";
	Planet mercury(0.4879f, mercuryTexturePath);
	glm::vec3 mercuryPos = glm::vec3(579.0f / 1.2f, 0.0f, 0.0f);
	mercury.setPosition(mercuryPos);

	std::string venusTexturePath = "assets/venus.png";
	Planet venus(1.2104f, venusTexturePath);
	glm::vec3 venusPos = glm::vec3(1082.0f / 1.2f, 0.0f, 0.0f);
	venus.setPosition(venusPos);

	std::string earthTexturePath = "assets/earth.png";
	Planet earth(1.2756f, earthTexturePath);
	glm::vec3 earthPos = glm::vec3(1496.0f / 1.2f, 0.0f, 0.0f);
	earth.setPosition(earthPos);

	std::string marsTexturePath = "assets/mars.png";
	Planet mars(0.6779f, marsTexturePath);
	glm::vec3 marsPos = glm::vec3(2279.0f / 1.2f, 0.0f, 0.0f);
	mars.setPosition(marsPos);

	std::string jupiterTexturePath = "assets/jupiter.png";
	Planet jupiter(14.2984f, jupiterTexturePath);
	glm::vec3 jupiterPos = glm::vec3(7786.0f / 1.2f, 0.0f, 0.0f);
	jupiter.setPosition(jupiterPos);

	std::string saturnTexturePath = "assets/saturn.png";
	Planet saturn(12.0000f, saturnTexturePath);
	glm::vec3 saturnPos = glm::vec3(14335.0f / 1.2f, 0.0f, 0.0f);
	saturn.setPosition(saturnPos);
	
	std::string uranusTexturePath = "assets/uranus.png";
	Planet uranus(5.1118f, uranusTexturePath);
	glm::vec3 uranusPos = glm::vec3(28725.0f / 1.2f, 0.0f, 0.0f);
	uranus.setPosition(uranusPos);

	std::string neptuneTexturePath = "assets/neptune.png";
	Planet neptune(4.9244f, neptuneTexturePath);
	glm::vec3 neptunePos = glm::vec3(44951.0f / 1.2f, 0.0f, 0.0f);
	neptune.setPosition(neptunePos);
    
    
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

		sun.draw(proj, view);
		mercury.draw(proj, view);
		venus.draw(proj, view);
		earth.draw(proj, view);
		mars.draw(proj, view);
		jupiter.draw(proj, view);
		saturn.draw(proj, view);
		uranus.draw(proj, view);
		neptune.draw(proj, view);

		glfwPollEvents();
		glfwSwapBuffers(window.getWindow());
	}

	return 0;
}