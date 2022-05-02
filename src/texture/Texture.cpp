#include "Texture.h"

#include <iostream>

Texture::Texture(const char* path)
	: Texture(path, "texture")
{
}

Texture::Texture(const char* path, std::string type)
	: Texture(path, type, GL_TEXTURE_2D)
{
}

Texture::Texture(const char* path, std::string type, GLenum target)
	: target(target) 
	, type(type)
{
	id = loadTexture(path);
}

void Texture::bind()
{
	glBindTexture(target, id);
	CHECK_GL_ERROR();
}

void Texture::bind(int typeIndex, GLuint textureUnit, PhongShader& shader)
{
	//Activate texture unit
	glActiveTexture(GL_TEXTURE0+ textureUnit);
	//Find appropriate sampler and set its texture unit
	glUniform1i(glGetUniformLocation(shader.id, (type + std::to_string(typeIndex)).c_str()), textureUnit);
	//Also enable flag saying this sampler is active
	glUniform1i(glGetUniformLocation(shader.id, (type + std::to_string(typeIndex) + "_active").c_str()), GL_TRUE);
	//Bind the texture to that texture unit
	bind();
}

void Texture::dispose() {
	glDeleteTextures(1, &id);
}

void Texture::setClampToEdge() {
    this->bind();
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
}

GLuint Texture::loadTexture(const char* path)
{
	std::cout << "Loading texture file: " << path << std::endl;
	return pgr::createTexture(path);
}
