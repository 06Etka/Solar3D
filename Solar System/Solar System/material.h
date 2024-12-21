#ifndef MATERIAL_H
#define MATERIAL_H

#include "component.h"
#include "camera.h"
#include "transform.h"
#include "shader.h"

class Material : public Component
{
public:
	Material(Camera& camera, Transform& transform, std::string shaderName);

	void update(float deltaTime) override;

private:
	Shader* shader;
	Camera& camera;
	Transform& transform;
};

#endif // !MATERIAL_H
