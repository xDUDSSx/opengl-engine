#pragma once

#include "Texture.h"

/**
 * \brief A set of textures for multi-mapping.
 */
struct TextureSet {
	Texture* texture = nullptr;
	Texture* specularMap = nullptr;
	Texture* normalMap = nullptr;
	Texture* aoMap = nullptr;
	Texture* emissionMap = nullptr;
	float normalStrength = 1.0f;
};
