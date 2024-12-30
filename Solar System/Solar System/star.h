#ifndef STAR_H
#define STAR_H

#include "celestial_body.h"
#include "shader.h"
#include "camera.h"

class Star : public CelestialBody
{
public:
	Star(const std::string& texturePath, float mass);

	void update(float deltaTime);
	void render();

private:
	Shader* shader;
	Camera& camera;
};

#endif // !STAR_H
