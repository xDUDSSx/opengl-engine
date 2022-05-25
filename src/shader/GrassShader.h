#pragma once

#include "PhongShader.h"

class GrassShader : public PhongShader {
public:
	GrassShader(const std::string& vertShader, const std::string& fragShader);

	void setUniforms() override;
};
