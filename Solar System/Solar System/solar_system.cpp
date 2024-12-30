#include "solar_system.h"

#include "imgui/imgui.h"

#pragma region MERCURY
const float MERCURY_MASS = 0.330f;
float mercuryOrbitRadius = 57.9f;
float mercruyEccentricity = 0.206f;
float mercuryDiameter = 0.4879f;
float mercuryStartPos = 57.9f;
#pragma endregion

#pragma region VENUS
const float VENUS_MASS = 4.87f;
float venusOrbitRadius = 108.2f;
float venusEccentricity = 0.007f;
float venusDiameter = 1.2104f;
float venusStartPos = 108.2f;
#pragma endregion

#pragma region EARTH
const float EARTH_MASS = 5.97f;
float earthOrbitRadius = 149.6f;
float earthEccentricity = 0.017f;
float earthDiameter = 1.2756f;
float earthStartPos = 149.6f;
#pragma endregion

#pragma region MARS
const float MARS_MASS = 0.642f;
float marsOrbitRadius = 228.0f;
float marsEccentricity = 0.094f;
float marsDiameter = 0.6792f;
float marsStartPos = 228.0f;
#pragma endregion


SolarSystem::SolarSystem() 
{
	sun = new Star("assets/textures/sun.png", 1.989f);
	sun->setScale(glm::vec3(13.92f));
	addPlanet("assets/textures/mercury.png", sun, MERCURY_MASS, mercuryOrbitRadius, mercruyEccentricity, glm::vec3(mercuryDiameter), glm::vec3(mercuryStartPos, 0.0f, 0.0f));
	addPlanet("assets/textures/venus.png", sun, VENUS_MASS, venusOrbitRadius, venusEccentricity, glm::vec3(venusDiameter), glm::vec3(venusStartPos, 0.0f, 0.0f));
	addPlanet("assets/textures/earth.png", sun, EARTH_MASS, earthOrbitRadius, earthEccentricity, glm::vec3(earthDiameter), glm::vec3(earthStartPos, 0.0f, 0.0f));
	addPlanet("assets/textures/mars.png", sun, MARS_MASS, marsOrbitRadius, marsEccentricity, glm::vec3(marsDiameter), glm::vec3(marsStartPos, 0.0f, 0.0f));
}

void SolarSystem::update(float deltaTime) {
	sun->update(deltaTime);

	for (auto& planet : planets)
	{
		planet.update(deltaTime);
	}
}

void SolarSystem::render() {
	sun->render();

	for (auto& planet : planets)
	{
		planet.render();
	}
}

void SolarSystem::addPlanet(const std::string& texturePath, CelestialBody* orbitParent, float mass, float orbitRadius, float eccentricity, glm::vec3 scale, glm::vec3 position) {
	Planet newPlanet(texturePath, orbitParent, mass, orbitRadius, eccentricity);
	newPlanet.setScale(scale);
	newPlanet.setPosition(position);
	planets.emplace_back(newPlanet);
}