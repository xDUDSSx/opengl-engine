#pragma once

#include <memory>
#include <vector>

#include "entity/lights/Light.h"
#include "shader/PhongShader.h"

class Lighting {
private:
    std::vector<std::shared_ptr<Light>> lights;

public:
    void setUniforms(const PhongShader& shader) const;
    void addLight(Light* light);
    void addLight(const std::shared_ptr<Light>& light);
    void removeLight(std::shared_ptr<Light>& light);
    std::vector<std::shared_ptr<Light>> getLights() const;
};
