#ifndef TEXTURE_H
#define TEXTURE_H

#include <iostream>
#include <string>

#include <glad/glad.h>

#include "stb_image.h"

class Texture
{
public:
	Texture(const std::string& texturePath);
	
	void bindTexture() const;

private:
	void loadTexture(const std::string& texturePath);

	unsigned int texture;
	int width, height, nrChannels;
	unsigned char* data;
};

#endif // !TEXTURE_H
