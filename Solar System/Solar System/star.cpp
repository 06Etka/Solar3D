#include "star.h"

Star::Star(const std::string& texturePath, float mass)
	: CelestialBody(texturePath, mass), camera(Camera::getInstance())
{
	shader = new Shader("star.vert", "star.frag");
}

void Star::update(float deltaTime) {
	float angularSpeed = 1.2f;
	float deltaRotation = angularSpeed * deltaTime;

	glm::vec3 currentRotation = getRotation();
	currentRotation.y += deltaRotation;

	setRotation(currentRotation);
}

void Star::render() {
	shader->use();
	shader->setMat4("projection", camera.getProjectionMatrix());
	shader->setMat4("view", camera.getViewMatrix());
	shader->setMat4("model", getModel());
	CelestialBody::render();
}