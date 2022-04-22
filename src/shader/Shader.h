#pragma once

#include "pgr.h";

class Shader {
public:
	GLuint id;
    
    virtual void use();

    Shader(const std::string& vertShader, const std::string& fragShader);
};
