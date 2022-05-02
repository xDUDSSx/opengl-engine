#include "GrassShader.h"

#include "../Game.h"

GrassShader::GrassShader(const std::string& vertShader, const std::string& fragShader)
: PhongShader(vertShader, fragShader)
{
	//Empty
}

void GrassShader::setUniforms() {
	PhongShader::setUniforms();

	glUniform1f(glGetUniformLocation(id, "time"), Game::time);
	glUniform1f(glGetUniformLocation(id, "windStrength"), Game::windStrength);

	CHECK_GL_ERROR();
}
