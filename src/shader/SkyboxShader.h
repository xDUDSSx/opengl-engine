#pragma once

#include "Shader.h"

class SkyboxShader : public Shader {
public:
    // Attributes
    GLuint aPos;

    // Uniforms
    GLuint pvMatrixId;

    // Sampler
    GLuint samplerId;

    SkyboxShader(const std::string& vertShader, const std::string& fragShader);

    /**
     * \brief Applies view and projection matrices.
     * \param view View matrix
     * \param projection Projection matrix
     */
    void setTransformUniforms(const glm::mat4& view, const glm::mat4& projection) const;
};
