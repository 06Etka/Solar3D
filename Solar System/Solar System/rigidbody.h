#ifndef RIGIDBODY_H
#define RIGIDBODY_H

#include <glm/glm.hpp>

#include "component.h"
#include "transform.h"

class Rigidbody : public Component
{
public:
	Rigidbody(Transform& transform);

	void update(float deltaTime) override;

	void addForce(glm::vec3 force);
	void setMass(float mass);

private:
	glm::vec3 velocity;
	glm::vec3 forceAccummulator;
	float mass;

	Transform& transform;
};

#endif // !RIGIDBODY_H
