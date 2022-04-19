#include "PhongShader.h"

PhongShader::PhongShader(const std::string& vertShader, const std::string& fragShader)
	: Shader(vertShader, fragShader)
{
    aPos = 0;
    aColor = 1;
    aTexCoord = 2;
    aNormal = 3;

    pvmMatrixId = glGetUniformLocation(id, "pvmMatrix");
    modelMatrixId = glGetUniformLocation(id, "modelMatrix");
    viewMatrixId = glGetUniformLocation(id, "viewMatrix");
    normalMatrixId = glGetUniformLocation(id, "normalMatrix");
}

void PhongShader::setTransformUniforms(const glm::mat4& model, const glm::mat4& view, const glm::mat4& projection) const {
    glm::mat4 pvm = projection * view * model;
    const glm::mat4 modelRotationMatrix = glm::mat4(
        model[0],
        model[1],
        model[2],
        glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
    glm::mat4 normalMatrix = glm::transpose(glm::inverse(modelRotationMatrix));

    glUniformMatrix4fv(pvmMatrixId, 1, GL_FALSE, glm::value_ptr(pvm));
	glUniformMatrix4fv(viewMatrixId, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(modelMatrixId, 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(normalMatrixId, 1, GL_FALSE, glm::value_ptr(normalMatrix));

    CHECK_GL_ERROR();
}
