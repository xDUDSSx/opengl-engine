#include "SunLight.h"

void SunLight::setUniforms(const PhongShader& shader, int index) const {
    const std::string prefix = "sunLights[" + std::to_string(index) + "]";
    glUniform1f(glGetUniformLocation(shader.id, (prefix + ".intensity").c_str()), intensity);
    glUniform3fv(glGetUniformLocation(shader.id, (prefix + ".color").c_str()), 1, glm::value_ptr(color));
    glUniform3fv(glGetUniformLocation(shader.id, (prefix + ".direction").c_str()), 1, glm::value_ptr(direction));
}

std::string SunLight::getName() {
    if (name.empty())
        return "Sun Light " + std::to_string(id);
    return name;
}
