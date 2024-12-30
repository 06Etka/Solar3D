#include "mesh.h"

Mesh::Mesh() {
	createSphere(vertices, indices);
}

void Mesh::createSphere(std::vector<Vertex>& vertices, std::vector<Index>& indices) {
    for (unsigned int ring = 0; ring <= RINGS; ++ring) {
        float theta = ring * M_PI / RINGS;
        for (unsigned int segment = 0; segment <= SEGMENTS; ++segment) {
            float phi = segment * 2 * M_PI / SEGMENTS;

            Vertex vertex;
            vertex.position.x = RADIUS * sin(theta) * cos(phi);
            vertex.position.y = RADIUS * sin(theta) * sin(phi);
            vertex.position.z = RADIUS * cos(theta);

            vertex.normal.x = sin(theta) * cos(phi);
            vertex.normal.y = sin(theta) * sin(phi);
            vertex.normal.z = cos(theta);

            vertex.texCoords.x = phi / (2 * M_PI);
            vertex.texCoords.y = (M_PI / 2 - theta) / M_PI;

            vertices.push_back(vertex);
        }
    }

    for (unsigned int ring = 0; ring < RINGS; ++ring) {
        for (unsigned int segment = 0; segment < SEGMENTS; ++segment) {
            unsigned int first = (ring * (SEGMENTS + 1)) + segment;
            unsigned int second = first + SEGMENTS + 1;

            indices.push_back({ first, second, first + 1 });

            indices.push_back({ second, second + 1, first + 1 });
        }
    }
}