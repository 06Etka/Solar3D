#include "transform.h"


Transform::Transform() 
	: position(0.0f), rotation(0.0f), scale(1.0f), modelMatrix(1.0f)
{

}

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

	modelMatrix = glm::rotate(modelMatrix, rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
	modelMatrix = glm::rotate(modelMatrix, rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
	modelMatrix = glm::rotate(modelMatrix, rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));

	modelMatrix = glm::scale(modelMatrix, scale);
}