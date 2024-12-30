#include "transform.h"


Transform::Transform() 
	: position(0.0f), rotation(0.0f), scale(1.0f), modelMatrix(1.0f) {}

void Transform::setPosition(const glm::vec3& newPos) {
	position = newPos;
	updateModelMatrix();
}

glm::vec3 Transform::getPosition() const { return position; }

void Transform::setRotation(const glm::vec3& newRot) {
	rotation = newRot;
	updateModelMatrix();
}

glm::vec3 Transform::getRotation() const { return rotation; }

void Transform::setScale(const glm::vec3& newScl) {
	scale = newScl;
	updateModelMatrix();
}

glm::vec3 Transform::getScale() const { return scale; }

void Transform::setModel(const glm::mat4& model) {
	modelMatrix = model;
}

glm::mat4 Transform::getModel() const { return modelMatrix; }

void Transform::updateModelMatrix() {
	modelMatrix = glm::mat4(1.0f);

	modelMatrix = glm::translate(modelMatrix, position);

	glm::quat quaternionRotation = glm::quat(glm::radians(rotation));
	modelMatrix *= glm::mat4_cast(quaternionRotation);

	modelMatrix = glm::scale(modelMatrix, scale);
}