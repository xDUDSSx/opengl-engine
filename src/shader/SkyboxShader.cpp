#include "SkyboxShader.h"

SkyboxShader::SkyboxShader(const std::string& vertShader, const std::string& fragShader)
: Shader(vertShader, fragShader)
{
    aPos = 0;

    pvMatrixId = glGetUniformLocation(id, "pvMatrix");

    samplerId = glGetUniformLocation(id, "cubemap");
}

void SkyboxShader::setTransformUniforms(const glm::mat4& view, const glm::mat4& projection) const
{
    glm::mat4 viewNoTranslation = glm::mat4(glm::mat3(view));
    glm::mat4 viewNoT = glm::mat4(
        view[0],
        view[1],
        view[2],
        glm::vec4(0, 0, 0, 1)
    );
    glm::mat4 pvMatrix = projection * viewNoT;

    glUniformMatrix4fv(pvMatrixId, 1, GL_FALSE, glm::value_ptr(pvMatrix));

    CHECK_GL_ERROR();
}