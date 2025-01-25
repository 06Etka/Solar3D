#include "planet.h"

Planet::Planet(const std::string& texturePath, CelestialBody* orbitParent, float mass, float orbitRadius, float eccentricity, float rotationPeriod)
	: camera(Camera::getInstance()), CelestialBody(texturePath, mass), orbitParent(orbitParent), orbitRadius(orbitRadius), eccentricity(eccentricity),
	rotationPeriod(rotationPeriod)
{
	shader = new Shader("planet.vert", "planet.frag");
}

void Planet::updateRotation(float deltaTime) {
	float angularSpeed = 2.0f * M_PI / rotationPeriod;

	float deltaRotation = angularSpeed * deltaTime;

	glm::vec3 currentRotation = getRotation();
	currentRotation.y += deltaRotation;

	setRotation(currentRotation);
}

void Planet::updatePosition(float deltaTime) {
	float semiMajorAxis = orbitRadius;
	float semiMinorAxis = orbitRadius * sqrt(1 - eccentricity * eccentricity);

	float distance = semiMajorAxis * (1 - eccentricity * eccentricity) / (1 + eccentricity * cos(angle));

	float angularSpeed = sqrt(orbitParent->getMass() * 6.8f / (semiMajorAxis * semiMajorAxis));
	angle += angularSpeed * deltaTime;

	float newPosX = orbitParent->getPosition().x + distance * cos(angle);
	float newPosZ = orbitParent->getPosition().z + distance * sin(angle);

	setPosition(glm::vec3(newPosX, 0, newPosZ));
}

void Planet::update(float deltaTime) {
	updateRotation(deltaTime);
	updatePosition(deltaTime);
}

void Planet::render() {
	shader->use();
	shader->setMat4("projection", camera.getProjectionMatrix());
	shader->setMat4("view", camera.getViewMatrix());
	shader->setMat4("model", CelestialBody::getModel());
	shader->setVec3("lightColor", glm::vec3(1.0f));
	shader->setVec3("lightPos", orbitParent->getPosition());
	CelestialBody::render();
}