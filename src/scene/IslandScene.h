#pragma once

#include "Scene.h"
#include "../Lighting.h"
#include "../texture/TextureManager.h"

/**
 * \brief As there are no configuration files / file scene loading capabilities yet this method
 * serves as a hardcoded configuration file alternative. Creates the default floating island scene.
 * \param scene The scene
 * \param lighting Lighting manager
 * \param shader Main shader
 * \param grassShader Special grass shader
 * \param airshipCamera Camera attached to the airship circling the island
 */
void createIslandScene(Scene* scene, Lighting* lighting, TextureManager* textures, PhongShader* shader, PhongShader* grassShader, Camera* airshipCamera);
