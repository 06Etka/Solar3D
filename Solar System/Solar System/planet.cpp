#include "planet.h"

Planet::Planet(const float radius, std::string& texturePath) : radius(radius) {
	setupMesh();
    textureLoader.loadTexture(texturePath);
}

void Planet::setupMesh() {
	createUVSphere(radius, rings, segments, vertices, indices);

    shader = new Shader("default.vert", "default.frag");

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(Index), indices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoords));
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Planet::createUVSphere(float radius, unsigned int rings, unsigned int segments,
    std::vector<Vertex>& vertices, std::vector<Index>& indices) {
    for (unsigned int ring = 0; ring <= rings; ++ring) {
        float theta = ring * 3.14159f / rings;
        for (unsigned int segment = 0; segment <= segments; ++segment) {
            float phi = segment * 2 * 3.14159f / segments;

            Vertex vertex;
            vertex.position.x = radius * sin(theta) * cos(phi);
            vertex.position.y = radius * sin(theta) * sin(phi);
            vertex.position.z = radius * cos(theta);

            vertex.normal.x = sin(theta) * cos(phi);
            vertex.normal.y = sin(theta) * sin(phi);
            vertex.normal.z = cos(theta);

            vertex.texCoords.x = phi / (2 * 3.14f);
            vertex.texCoords.y = (3.14f / 2 - theta) / 3.14f;

            vertices.push_back(vertex);
        }
    }

    for (unsigned int ring = 0; ring < rings; ++ring) {
        for (unsigned int segment = 0; segment < segments; ++segment) {
            unsigned int first = (ring * (segments + 1)) + segment;
            unsigned int second = first + segments + 1;

            indices.push_back({ first, second, first + 1 });

            indices.push_back({ second, second + 1, first + 1 });
        }
    }
}

void Planet::draw(glm::mat4& proj, glm::mat4& view) {
    textureLoader.bindTexture();
    shader->use();
    shader->setMat4("projection", proj);
    shader->setMat4("view", view);
    shader->setMat4("model", getModel());

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size() * 3, GL_UNSIGNED_INT, 0);
}