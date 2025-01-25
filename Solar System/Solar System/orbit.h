#ifndef ORBIT_H
#define ORBIT_H

#include <vector>

#include "camera.h"
#include "shader.h"

class Orbit
{
public:
	Orbit(float orbitRadius, float eccentricity);

	void render();

private:
	std::vector<float> calculateOrbit();

	const int POINTS = 360;
	float orbitRadius;
	float eccentricity;

	std::vector<float> vertices;


	void setupMesh();

	unsigned int VAO, VBO;

	Shader* shader;
};

#endif // !ORBIT_H
