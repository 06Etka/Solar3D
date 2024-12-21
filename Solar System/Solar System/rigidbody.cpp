#include "rigidbody.h"

Rigidbody::Rigidbody(Transform& transform) 
	: transform(transform), velocity(glm::vec3(0.0f)), forceAccummulator(glm::vec3(0.0f)) {}

void Rigidbody::update(float deltaTime) {
	glm::vec3 acceleration = forceAccummulator / mass;
	velocity += acceleration * deltaTime;

	glm::vec3 newPos = transform.getPosition() + velocity * deltaTime;
	transform.setPosition(newPos);

	forceAccummulator = glm::vec3(0.0f);
}

void Rigidbody::addForce(glm::vec3 force) {
	forceAccummulator += force;
}

void Rigidbody::setMass(float mass) {
	this->mass = mass;
}