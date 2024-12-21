#ifndef PLANET_H
#define PLANET_H

#include <vector>
#include <string>
#include <memory>

#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

#include "transform.h"
#include "mesh.h"
#include "mesh_renderer.h"
#include "material.h"
#include "texture_loader.h"
#include "rigidbody.h"

class Planet : public Transform
{
public:
	Planet(Camera& camera, const std::string& shaderName, const std::string& texturePath);
	~Planet();

	void update(float deltaTime);

	float force = 0;

private:
	Mesh* mesh;
	MeshRenderer* meshRenderer;
	Material* material;
	TextureLoader* textureLoader;
	Rigidbody* rigidbody;
};

#endif // !PLANET_H
