#ifndef MESH_H
#define MESH_H

#define _USE_MATH_DEFINES
#include <math.h>
#include <vector>

#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

struct Vertex {
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texCoords;
};

struct Index {
	unsigned int v1, v2, v3;
};

class Mesh
{
public:
	Mesh();

	std::vector<Vertex> vertices;
	std::vector<Index> indices;
private:
	void createSphere(std::vector<Vertex>& vertices, std::vector<Index>& indices);

	const float RADIUS = 1;
	const unsigned int RINGS = 32;
	const unsigned int SEGMENTS = 32;
};

#endif // !MESH_H

