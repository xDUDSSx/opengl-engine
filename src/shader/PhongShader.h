#pragma once

#include "Shader.h"

class PhongShader : public Shader {
public:
    // Attributes
    GLuint aPos;
    GLuint aColor;
    GLuint aTexCoord;
    GLuint aNormal;

    // Uniforms
    GLuint pvmMatrixId;
    GLuint modelMatrixId;
    GLuint viewMatrixId;
    GLuint normalMatrixId;

    // Precomputed
    glm::mat4 pvMatrix;

    PhongShader(const std::string& vertShader, const std::string& fragShader);

	void setTransformUniforms(const glm::mat4& model, const glm::mat4& view, const glm::mat4& projection) const;
};
