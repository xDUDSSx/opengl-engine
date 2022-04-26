#pragma once

#include "pgr.h"
#include "../shader/PhongShader.h"

class Texture {
public:
    GLuint id;
    GLenum target;
    std::string type;

    Texture(const char* path);
    Texture(const char* path, std::string type);
    Texture(const char* path, std::string type, GLenum target);

    void bind();
	void bind(int typeIndex, GLuint textureUnit, PhongShader& shader);

private:
    GLuint loadTexture(const char* path);
};
