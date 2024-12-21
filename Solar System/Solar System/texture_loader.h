#ifndef TEXTURE_LOADER_H
#define TEXTURE_LOADER_H

#include <iostream>
#include <string>

#include <glad/glad.h>

#include "stb_image.h"

class TextureLoader
{
public:
	void loadTexture(const std::string& path);

	void bindTexture() const;

private:
	unsigned int texture;
	int width, height, nrChannels;
	unsigned char* data;
};


#endif // !TEXTURE_LOADER_H
