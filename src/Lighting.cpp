#include "Lighting.h"

#include "entity/lights/PointLight.h"
#include "entity/lights/SpotLight.h"
#include "entity/lights/SunLight.h"

void Lighting::setUniforms(const PhongShader& shader) const {
    int pointLightCount = 0;
    int sunLightCount = 0;
    int spotLightCount = 0;
    for (auto& light : lights) {
        if (typeid(*light) == typeid(PointLight)) {
            light->setUniforms(shader, pointLightCount);
        	pointLightCount++;
        } else
        if (typeid(*light) == typeid(SunLight)) {
            light->setUniforms(shader, sunLightCount);
        	sunLightCount++;
        } else 
        if (typeid(*light) == typeid(SpotLight)) {
            light->setUniforms(shader, spotLightCount);
            spotLightCount++;
        }
    }
    glUniform1i(glGetUniformLocation(shader.id, "pointLightsCount"), pointLightCount);
    glUniform1i(glGetUniformLocation(shader.id, "sunLightsCount"), sunLightCount);
    glUniform1i(glGetUniformLocation(shader.id, "spotLightsCount"), spotLightCount);
}

void Lighting::addLight(Light* light) {
    const auto newLight = std::shared_ptr<Light>(light);
    lights.push_back(newLight);
}

void Lighting::addLight(const std::shared_ptr<Light>& light) {
    lights.push_back(light);
}

void Lighting::removeLight(std::shared_ptr<Light>& light) {
    auto it = std::find(lights.begin(), lights.end(), light);
    if (it != lights.end()) {
        lights.erase(it);
    }
}

std::vector<std::shared_ptr<Light>> Lighting::getLights() const {
    return lights;
}
