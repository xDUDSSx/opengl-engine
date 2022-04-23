#include "NormalDebugShader.h"

NormalDebugShader::NormalDebugShader(const std::string& vertShader, const std::string& fragShader, const std::string* geoShader)
	: PhongShader(vertShader, fragShader, geoShader)
{
	//Empty
}
