#pragma once

#include "pgr.h"
#include "mesh/MeshManager.h"
#include "texture/TextureManager.h"

/**
 * \brief Static global variables container.
 */
class Game {
public:
	static float time;

	static std::unique_ptr<TextureManager> textures;
	static std::unique_ptr<MeshManager> meshes;

	static bool drawDebugNormals;
	static float normalDebugShaderMagnitude;

	static float windStrength;
	static float animSpeed;

	static bool fogEnabled;
	static glm::vec3 fogColor;
	static float fogNear;
	static float fogFar;

	static bool cameraCollision;

	static bool disableLighting;
	static bool disableNormalMapping;
};
