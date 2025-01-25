#include "orbit.h"

Orbit::Orbit(float orbitRadius, float eccentricity) : orbitRadius(orbitRadius), eccentricity(eccentricity) {
	vertices = calculateOrbit();
    shader = new Shader("orbit.vert", "orbit.frag");
    setupMesh();
}

std::vector<float> Orbit::calculateOrbit() {
    std::vector<float> vertices;
    double focusDistance = orbitRadius * eccentricity;

    for (int i = 0; i < POINTS; ++i) {
        double theta = glm::two_pi<double>() * i / POINTS;

        double r = orbitRadius * (1 - eccentricity * eccentricity) / (1 + eccentricity * cos(theta));

        float x = static_cast<float>(r * cos(theta) + focusDistance);
        float y = static_cast<float>(r * sin(theta));

        x -= static_cast<float>(focusDistance);

        vertices.push_back(x);
        vertices.push_back(0.0f);
        vertices.push_back(y);
    }

    return vertices;
}



void Orbit::setupMesh() {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
}

void Orbit::render() {
    glm::mat4 model = glm::mat4(1.0f);
    shader->use();
    shader->setMat4("projection", Camera::getInstance().getProjectionMatrix());
    shader->setMat4("view", Camera::getInstance().getViewMatrix());
    shader->setMat4("model", model);

    glBindVertexArray(VAO);
    glDrawArrays(GL_LINE_LOOP, 0, vertices.size() / 3);
}