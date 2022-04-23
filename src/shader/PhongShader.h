#pragma once

#include "Shader.h"

class PhongShader : public Shader {
public:
    // Attributes
    GLuint aPos;
    GLuint aColor;
    GLuint aTexCoord;
    GLuint aNormal;
    GLuint aTangent;

    // Uniforms
    GLuint pvmMatrixId;
    GLuint modelMatrixId;
    GLuint viewMatrixId;
    GLuint normalMatrixId;

    // Precomputed
    glm::mat4 pvMatrix;

    PhongShader(const std::string& vertShader, const std::string& fragShader);

    /**
     * \brief Applies MVP matrices.
     * \param model Model matrix
     * \param view View matrix
     * \param projection Projection matrix
     */
    void setTransformUniforms(const glm::mat4& model, const glm::mat4& view, const glm::mat4& projection) const;

    /**
     * \brief Sets all texture active flags to false. Used to reset texture state before binding new set of textures.
     */
    void clearTextures() const;
};
