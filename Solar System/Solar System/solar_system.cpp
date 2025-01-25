#include "solar_system.h"

SolarSystem::SolarSystem() 
{
	sun = new Star("assets/textures/sun.png", 1.989f);
	sun->setScale(glm::vec3(14.0f));

    std::ifstream inputFile("assets/planets.json");

    if (!inputFile.is_open()) {
        std::cerr << "Failed to open the file!" << std::endl;
        return;
    }

    nlohmann::json jsonData;
    inputFile >> jsonData;

    auto planets = jsonData["planets"];

    for (const auto& planet : planets) {
        std::string name = planet["name"];
        std::string texturePath = planet["texture"];
        double mass = planet["mass"];
        double distance = planet["distance_from_sun"];
        double eccentricity = planet["eccentricity"];
        double diameter = planet["diameter"];
        double rotationPeriod = planet["rotation_period"];

        addPlanet(texturePath, sun, mass, distance, eccentricity, rotationPeriod, glm::vec3(diameter / 1.5f), glm::vec3(distance, 0.0f, 0.0f));

        Orbit newOrbit(distance, eccentricity);
        orbits.emplace_back(newOrbit);
    }
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

    for (auto& orbit : orbits)
    {
        orbit.render();
    }
}

void SolarSystem::addPlanet(const std::string& texturePath, CelestialBody* orbitParent, float mass, float orbitRadius, float eccentricity, float rotationPeriod, glm::vec3 scale, glm::vec3 position) {
	Planet newPlanet(texturePath, orbitParent, mass, orbitRadius, eccentricity, rotationPeriod);
	newPlanet.setScale(scale);
	newPlanet.setPosition(position);
	planets.emplace_back(newPlanet);
}