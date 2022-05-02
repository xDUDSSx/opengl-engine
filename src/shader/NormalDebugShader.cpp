#include "NormalDebugShader.h"

#include "../Game.h"

NormalDebugShader::NormalDebugShader(const std::string& vertShader, const std::string& fragShader, const std::string* geoShader)
	: PhongShader(vertShader, fragShader, geoShader)
{
	//Empty
}

void NormalDebugShader::setUniforms()
{
	PhongShader::setUniforms();

    glUniform1f(glGetUniformLocation(id, "magnitude"), Game::normalDebugShaderMagnitude);
}
