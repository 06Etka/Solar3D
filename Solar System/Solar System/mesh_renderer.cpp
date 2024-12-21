#include "mesh_renderer.h"

MeshRenderer::MeshRenderer(Mesh* mesh, Material* material) : 
    mesh(mesh), material(material) 
{
	setupMesh();
}

void MeshRenderer::update(float deltaTime) {
    material->update(deltaTime);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, mesh->indices.size() * 3, GL_UNSIGNED_INT, 0);
}

void MeshRenderer::setupMesh() {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, mesh->vertices.size() * sizeof(Vertex), mesh->vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh->indices.size() * sizeof(Index), mesh->indices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoords));
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}