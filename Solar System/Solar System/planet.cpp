#include "planet.h"

Planet::Planet(Camera& camera, const std::string& shaderName, const std::string& texturePath){
	textureLoader = new TextureLoader();
	if (texturePath.length() > 0) {
		textureLoader->loadTexture(texturePath);
	}
	mesh = new Mesh();
	material = new Material(camera, *this, shaderName);
	meshRenderer = new MeshRenderer(mesh, material);
	
	rigidbody = new Rigidbody(*this);
}

Planet::~Planet() {
	delete mesh;
	delete material;
	delete meshRenderer;
	delete textureLoader;
	delete rigidbody;
}

void Planet::update(float deltaTime) {
	rigidbody->update(deltaTime);
	textureLoader->bindTexture();
	meshRenderer->update(deltaTime);
}