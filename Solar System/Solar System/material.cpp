#include "material.h"

Material::Material(Camera& camera, Transform& transform, std::string shaderName)
	: camera(camera), transform(transform) {
	std::string vertShader = shaderName + ".vert";
	std::string fragShader = shaderName + ".frag";
	shader = new Shader(vertShader.c_str(), fragShader.c_str());
}

void Material::update(float deltaTime) {
	shader->use();
	shader->setMat4("projection", camera.getProjectionMatrix());
	shader->setMat4("view", camera.getViewMatrix());
	shader->setMat4("model", transform.getModel());
}