#ifndef SOLAR_SYSTEM_H
#define SOLAR_SYSTEM_H

#include <nlohmann/json.hpp>
#include <iostream>
#include <fstream>
#include <vector>

#include "star.h"
#include "planet.h"
#include "orbit.h"

class SolarSystem
{
public:
	SolarSystem();
	
	void update(float deltaTime);
	void render();

private:
	void addPlanet(const std::string& texturePath, CelestialBody* orbitParent, 
		float mass, float orbitRadius, float eccentricity, float rotationPeriod, glm::vec3 scale, glm::vec3 position);

	Star* sun;
	std::vector<Planet> planets;
	std::vector<Orbit> orbits;
};

#endif // !SOLAR_SYSTEM_H
