#include "PhongShader.h"

#include "../Game.h"

#define MAX_DIFFUSE_TEXTURES 1
#define MAX_SPECULAR_TEXTURES 1
#define MAX_NORMAL_TEXTURES 1
#define MAX_AO_TEXTURES 1
#define MAX_EMISSION_TEXTURES 1

PhongShader::PhongShader(const std::string& vertShader, const std::string& fragShader)
	: PhongShader(vertShader, fragShader, nullptr)
{
    //Empty
}

PhongShader::PhongShader(const std::string& vertShader, const std::string& fragShader, const std::string* geoShader)
    : Shader(vertShader, fragShader, geoShader)
{
    aPos = 0;
    aColor = 1;
    aTexCoord = 2;
    aNormal = 3;
    aTangent = 4;

    pvmMatrixId = glGetUniformLocation(id, "pvmMatrix");
    projectionMatrixId = glGetUniformLocation(id, "projectionMatrix");
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
    glUniformMatrix4fv(projectionMatrixId, 1, GL_FALSE, glm::value_ptr(projection));
	glUniformMatrix4fv(viewMatrixId, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(modelMatrixId, 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(normalMatrixId, 1, GL_FALSE, glm::value_ptr(normalMatrix));

    CHECK_GL_ERROR();
}

void PhongShader::setUniforms()
{
    // Time
    glUniform1f(glGetUniformLocation(id, "time"), Game::time);

    // Normal strength
    glUniform1f(glGetUniformLocation(id, "normalStrength"), 1.0f); //Default value

    // Fog
    glUniform1i(glGetUniformLocation(id, "fogEnabled"), Game::fogEnabled);
    glUniform3fv(glGetUniformLocation(id, "fogColor"), 1, glm::value_ptr(Game::fogColor));
	glUniform1f(glGetUniformLocation(id, "fogNear"), Game::fogNear);
    glUniform1f(glGetUniformLocation(id, "fogFar"), Game::fogFar);

    // UV matrix
    glUniform1f(glGetUniformLocation(id, "uvMatActive"), false);
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
    type = "normal";
    for (int i = 0; i < MAX_NORMAL_TEXTURES; i++) {
        glUniform1i(glGetUniformLocation(id, (type + std::to_string(i) + "_active").c_str()), GL_FALSE);
    }
    type = "ao";
    for (int i = 0; i < MAX_AO_TEXTURES; i++) {
        glUniform1i(glGetUniformLocation(id, (type + std::to_string(i) + "_active").c_str()), GL_FALSE);
    }
    type = "emission";
    for (int i = 0; i < MAX_EMISSION_TEXTURES; i++) {
        glUniform1i(glGetUniformLocation(id, (type + std::to_string(i) + "_active").c_str()), GL_FALSE);
    }
}
