#pragma once

#include "pgr.h"

class Shader {
public:
	GLuint id;

    Shader(const std::string& vertShader, const std::string& fragShader);
    Shader(const std::string& vertShader, const std::string& fragShader, const std::string* geoShader);

    virtual void use();
    virtual void dispose();
};
