#ifndef MESH_RENDERER_H
#define MESH_RENDERER_H

#include <iostream>
#include <memory>

#include "mesh.h"
#include "camera.h"

#include <glad/glad.h>


class MeshRenderer
{
public:
	MeshRenderer(Mesh* mesh);

	void render();

private:
	void setupMesh();

	Mesh* mesh;

	unsigned int VAO, VBO, EBO;

};

#endif // !MESH_RENDERER_H
