#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Transform
{
public:
	Transform();

	void setPosition(glm::vec3& newPos);
	glm::vec3 getPosition() const;

	void setRotation(glm::vec3& newRot);
	glm::vec3 getRotation() const;

	void setScale(glm::vec3& newScl);
	glm::vec3 getScale() const;

	void setModel(glm::mat4& model);
	glm::mat4 getModel() const;

private:
	glm::mat4 modelMatrix;
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;

	void updateModelMatrix();

};
#endif // !TRANSFORM_H
