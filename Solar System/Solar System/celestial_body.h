#ifndef CELESTIAL_BODY_H
#define CELESTIAL_BODY_H

#include "mesh.h"
#include "mesh_renderer.h"
#include "texture.h"
#include "transform.h"

class CelestialBody : public Transform
{
public:
	CelestialBody(const std::string& texturePath, float mass);

	void render();

	float getMass() const;
private:
	Mesh* mesh;
	MeshRenderer* meshRenderer;
	Texture* texture;

	float mass;
};

#endif // !CELESTIAL_BODY_H
