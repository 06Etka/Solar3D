#include "mesh.h"

glm::vec3 normalize(const glm::vec3& v, float radius) {
    return glm::normalize(v) * radius;
}

unsigned int getMidpoint(unsigned int v1, unsigned int v2, std::vector<Vertex>& vertices,
    std::map<std::pair<unsigned int, unsigned int>, unsigned int>& midpointCache, float radius) {
    if (v1 > v2) std::swap(v1, v2);

    auto edge = std::make_pair(v1, v2);
    if (midpointCache.find(edge) != midpointCache.end()) {
        return midpointCache[edge];
    }

    glm::vec3 midpoint = (vertices[v1].position + vertices[v2].position) * 0.5f;
    midpoint = normalize(midpoint, radius);

    Vertex newVertex = { midpoint, glm::normalize(midpoint), {0.0f, 0.0f} };
    vertices.push_back(newVertex);

    unsigned int midpointIndex = static_cast<unsigned int>(vertices.size() - 1);
    midpointCache[edge] = midpointIndex;
    
    return midpointIndex;
}

glm::vec2 calculateTexCoords(const glm::vec3& pos) {
    float u = 0.5f - (std::atan2(pos.z, pos.x) / (2.0f * M_PI));
    float v = 0.5f - (std::asin(pos.y) / M_PI);
    return { u, v };
}

void fixSeam(std::vector<Vertex>& vertices, std::vector<Index>& indices) {
    std::vector<Vertex> newVertices = vertices;
    std::vector<Index> newIndices;

    for (const auto& index : indices) {
        Vertex v1 = vertices[index.v1];
        Vertex v2 = vertices[index.v2];
        Vertex v3 = vertices[index.v3];

        if (std::abs(v1.texCoords.x - v2.texCoords.x) > 0.5f ||
            std::abs(v2.texCoords.x - v3.texCoords.x) > 0.5f ||
            std::abs(v3.texCoords.x - v1.texCoords.x) > 0.5f) {
            if (v1.texCoords.x > 0.5f) v1.texCoords.x -= 1.0f;
            if (v2.texCoords.x > 0.5f) v2.texCoords.x -= 1.0f;
            if (v3.texCoords.x > 0.5f) v3.texCoords.x -= 1.0f;

            unsigned int v1Index = static_cast<unsigned int>(newVertices.size());
            unsigned int v2Index = static_cast<unsigned int>(newVertices.size() + 1);
            unsigned int v3Index = static_cast<unsigned int>(newVertices.size() + 2);

            newVertices.push_back(v1);
            newVertices.push_back(v2);
            newVertices.push_back(v3);

            newIndices.push_back({ v1Index, v2Index, v3Index });
        }
        else {
            newIndices.push_back(index);
        }
    }

    vertices = newVertices;
    indices = newIndices;
}

void createIcosahedron(std::vector<Vertex>& vertices, std::vector<Index>& indices, float radius) {
    const float PHI = (1.0f + std::sqrt(5.0f)) / 2.0f;
    const float INV_LENGTH = 1.0f / std::sqrt(1.0f + PHI * PHI);

    std::vector<glm::vec3> positions = {
        {-1,  PHI,  0}, { 1,  PHI,  0}, {-1, -PHI,  0}, { 1, -PHI,  0},
        { 0, -1,  PHI}, { 0,  1,  PHI}, { 0, -1, -PHI}, { 0,  1, -PHI},
        { PHI,  0, -1}, { PHI,  0,  1}, {-PHI,  0, -1}, {-PHI,  0,  1}
    };

    for (auto& pos : positions) {
        pos *= INV_LENGTH;
        vertices.push_back({ normalize(pos, radius), glm::normalize(pos), {0.0f, 0.0f} });
    }

    std::vector<Index> baseIndices = {
        {0, 11, 5}, {0, 5, 1}, {0, 1, 7}, {0, 7, 10}, {0, 10, 11},
        {1, 5, 9}, {5, 11, 4}, {11, 10, 2}, {10, 7, 6}, {7, 1, 8},
        {3, 9, 4}, {3, 4, 2}, {3, 2, 6}, {3, 6, 8}, {3, 8, 9},
        {4, 9, 5}, {2, 4, 11}, {6, 2, 10}, {8, 6, 7}, {9, 8, 1}
    };

    indices.insert(indices.end(), baseIndices.begin(), baseIndices.end());
}

void subdivide(std::vector<Vertex>& vertices, std::vector<Index>& indices, unsigned int subdivisions, float radius) {
    for (unsigned int i = 0; i < subdivisions; ++i) {
        std::vector<Index> newIndices;
        std::map<std::pair<unsigned int, unsigned int>, unsigned int> midpointCache;

        for (const auto& tri : indices) {
            unsigned int a = getMidpoint(tri.v1, tri.v2, vertices, midpointCache, radius);
            unsigned int b = getMidpoint(tri.v2, tri.v3, vertices, midpointCache, radius);
            unsigned int c = getMidpoint(tri.v3, tri.v1, vertices, midpointCache, radius);

            newIndices.push_back({ tri.v1, a, c });
            newIndices.push_back({ tri.v2, b, a });
            newIndices.push_back({ tri.v3, c, b });
            newIndices.push_back({ a, b, c });
        }

        indices.swap(newIndices);
    }
}

void Mesh::createSphere(std::vector<Vertex>& vertices, std::vector<Index>& indices) {
    createIcosahedron(vertices, indices, RADIUS);
    subdivide(vertices, indices, SUBDIVISIONS, RADIUS);

    for (auto& vertex : vertices) {
        vertex.texCoords = calculateTexCoords(vertex.position);
    }

    fixSeam(vertices, indices);
}

Mesh::Mesh() {
    createSphere(vertices, indices);
}