#ifndef SOLAR_SYSTEM_H
#define SOLAR_SYSTEM_H

#include <vector>

#include "star.h"
#include "planet.h"

class SolarSystem
{
public:
	SolarSystem();
	
	void update(float deltaTime);
	void render();

private:
	void addPlanet(const std::string& texturePath, CelestialBody* orbitParent, 
		float mass, float orbitRadius, float eccentricity, glm::vec3 scale, glm::vec3 position);

	Star* sun;
	std::vector<Planet> planets;
};

#endif // !SOLAR_SYSTEM_H
