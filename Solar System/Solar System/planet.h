#ifndef PLANET_H
#define PLANET_H

#include <vector>

#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

#include "transform.h"
#include "shader.h"
#include "texture_loader.h"

struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoords;
};

struct Index {
    unsigned int v1, v2, v3;
};

class Planet : public Transform
{
public:
	Planet(const float radius, std::string& texturePath);

    void draw(glm::mat4& proj, glm::mat4& view);

private:
    void setupMesh();
    void createUVSphere(float radius, unsigned int rings, unsigned int segments, std::vector<Vertex>& vertices, std::vector<Index>& indices);

    const float radius;
    const unsigned int rings = 32;
    const unsigned int segments = 32;

    std::vector<Vertex> vertices;
    std::vector<Index> indices;

    unsigned int VAO, VBO, EBO;

    Shader* shader;
    TextureLoader textureLoader;
};

#endif // !PLANET_H
