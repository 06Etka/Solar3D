#include "celestial_body.h"

CelestialBody::CelestialBody(const std::string& texturePath, float mass) 
	: mass(mass)  {
	mesh = new Mesh();
	meshRenderer = new MeshRenderer(mesh);
	texture = new Texture(texturePath);
}

void CelestialBody::render() {
	texture->bindTexture();
	meshRenderer->render();
}

float CelestialBody::getMass() const { return mass; }