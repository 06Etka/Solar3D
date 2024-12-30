#ifndef PLANET_H
#define PLANET_H

#include <glm/gtc/type_ptr.hpp>

#include "celestial_body.h"
#include "shader.h"
#include "camera.h"

class Planet : public CelestialBody
{
public:
	Planet(const std::string& texturePath, CelestialBody* orbitParent, float mass, float orbitRadius, float eccentricity);

	void update(float deltaTime);
	void render();

private:
	Shader* shader;
	Camera& camera;

	CelestialBody* orbitParent;
	float orbitRadius;
	float eccentricity;
	float angle = 0.0f;
};

#endif // !PLANET_H
