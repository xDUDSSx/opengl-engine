#pragma once
#include "PhongShader.h"

class NormalDebugShader : public PhongShader {
public:
    NormalDebugShader(const std::string& vertShader, const std::string& fragShader, const std::string* geoShader);
};
