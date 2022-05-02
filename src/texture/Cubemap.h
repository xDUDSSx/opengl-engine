#pragma once
#include <string>
#include <vector>

#include "Texture.h"

class Cubemap {
public:
	GLuint id;

	Cubemap(std::vector<std::string> textures);

	void bind(GLuint location);

private:
	GLuint loadTextures(std::vector<std::string> textures);
};
