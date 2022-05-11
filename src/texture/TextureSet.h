#pragma once

#include "Texture.h"

struct TextureSet {
    std::shared_ptr<Texture> texture = nullptr;
    std::shared_ptr<Texture> specularMap = nullptr;
    std::shared_ptr<Texture> normalMap = nullptr;
    std::shared_ptr<Texture> aoMap = nullptr;
    std::shared_ptr<Texture> emissionMap = nullptr;
    float normalStrength = 1.0f;
};
