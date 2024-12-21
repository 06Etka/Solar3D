#ifndef MESH_RENDERER_H
#define MESH_RENDERER_H

#include <iostream>
#include <memory>

#include "component.h"
#include "mesh.h"
#include "material.h"
#include "camera.h"

#include <glad/glad.h>


class MeshRenderer : public Component
{
public:
	MeshRenderer(Mesh* mesh, Material* material = nullptr);

	void update(float deltaTime) override;

private:
	void setupMesh();

	Mesh* mesh;
	Material* material;

	unsigned int VAO, VBO, EBO;

};

#endif // !MESH_RENDERER_H
