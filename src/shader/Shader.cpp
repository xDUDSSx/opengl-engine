#include "Shader.h"

#include <iostream>

Shader::Shader(const std::string& vertShader, const std::string& fragShader)
	: Shader(vertShader, fragShader, nullptr)
{
	//Empty
}

Shader::Shader(const std::string& vertShader, const std::string& fragShader, const std::string* geoShader) {
	std::vector<GLuint> shaderList;

	// push vertex shader and fragment shader
	shaderList.push_back(pgr::createShaderFromFile(GL_VERTEX_SHADER, vertShader));
	shaderList.push_back(pgr::createShaderFromFile(GL_FRAGMENT_SHADER, fragShader));
	if (geoShader != nullptr) {
		shaderList.push_back(pgr::createShaderFromFile(GL_GEOMETRY_SHADER, *geoShader));    
	}

	this->id = pgr::createProgram(shaderList);

	if (this->id == 0) {
		std::cerr << "Failed to create shader program!" << std::endl;
	} else {
		printf("Created shader program with id: %d\n", this->id);
	}
}

void Shader::use()
{
	glUseProgram(id);
}

void Shader::dispose()
{
	pgr::deleteProgramAndShaders(id);
}