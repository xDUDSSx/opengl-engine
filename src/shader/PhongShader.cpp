#include "PhongShader.h"

#define MAX_DIFFUSE_TEXTURES 1
#define MAX_SPECULAR_TEXTURES 1
#define MAX_AO_TEXTURES 1
#define MAX_NORMAL_TEXTURES 1

PhongShader::PhongShader(const std::string& vertShader, const std::string& fragShader)
	: Shader(vertShader, fragShader)
{
    aPos = 0;
    aColor = 1;
    aTexCoord = 2;
    aNormal = 3;
    aTangent = 4;

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

void PhongShader::clearTextures() const {
    std::string type;
	type = "diffuse";
    for (int i = 0; i < MAX_DIFFUSE_TEXTURES; i++) {
        glUniform1i(glGetUniformLocation(id, (type + std::to_string(i) + "_active").c_str()), GL_FALSE);    
    }
    type = "specular";
    for (int i = 0; i < MAX_SPECULAR_TEXTURES; i++) {
        glUniform1i(glGetUniformLocation(id, (type + std::to_string(i) + "_active").c_str()), GL_FALSE);
    }
    type = "ao";
    for (int i = 0; i < MAX_AO_TEXTURES; i++) {
        glUniform1i(glGetUniformLocation(id, (type + std::to_string(i) + "_active").c_str()), GL_FALSE);
    }
    type = "normal";
    for (int i = 0; i < MAX_NORMAL_TEXTURES; i++) {
        glUniform1i(glGetUniformLocation(id, (type + std::to_string(i) + "_active").c_str()), GL_FALSE);
    }
}