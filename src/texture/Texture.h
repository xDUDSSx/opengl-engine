#pragma once

#include "pgr.h"
#include "../shader/PhongShader.h"

class Texture {
public:
    GLuint id;
    GLenum target;
    std::string type;
    const char* path;

    Texture(const char* path);
    Texture(const char* path, std::string type);
    Texture(const char* path, std::string type, GLenum target);

    void bind();
	void bind(int typeIndex, GLuint textureUnit, PhongShader& shader);
    void dispose();

    void setClampToEdge();

private:
    GLuint loadTexture(const char* path);
};
